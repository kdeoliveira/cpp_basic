// https://towardsdatascience.com/c-type-erasure-wrapping-any-type-7f8511634849
//  Lambda callback implementation
//  and type erasure to handle generic typing and wrapeprs

// any equivalent to void*
#include <any>

#include <memory>
#include <type_traits>
#include <utility>
#include <tuple>

// Template Metaprogramming - Gets parameters of templates in a reflective way at compile time
// Base case/struct template represents a function or callable object
template <typename Function>
struct function_traits :
    // remove_reference: gets raw type of Function (removes const, &, pointers, etc)
    // Note that this base case recursively inherits itself; Alternatively a second struct could be made for this inheritance
    public function_traits<decltype(&std::remove_reference<Function>::type::operator())>
{
};

// Recursive case/struct with implementation of function_traits
template <typename ReturnType, typename... Arguments>
struct function_traits<ReturnType (*)(Arguments...)>
{
    typedef ReturnType result_type;

    template <std::size_t Index>
    // std::tuple_element: indexed access to the types of the elements of the tuple
    //Note that this typing does not allow empty arguments
    using arg = typename std::tuple_element<
        Index,
        std::tuple<Arguments...>>::type;
    //Alternative with conditoinal (TODO)
    // template <std::size_t Index>
    // using arg = typename std::conditional<
    // sizeof(Index) => 1,
    // std::nullptr_t,
    // std::tuple_element<Index,std::tuple<Arguments...>>::type
    // >;

    static constexpr std::size_t arity = sizeof...(Arguments);
    static constexpr bool has_args = static_cast<bool>(arity);
};



// Recursive struct that provide support for static Class member functions (const or plain)
// Note that in case the member function is not static, the same must be first binded:
// std::fuction<void()> func = std::bind(&Class::method, &classObject);
// function_traits<func>
template <typename ClassType, typename ReturnType, typename... Arguments>
struct function_traits<ReturnType (ClassType::*)(Arguments...) const> : function_traits<ReturnType (*)(Arguments...)>
{
};

template <typename ClassType, typename ReturnType, typename... Arguments>
struct function_traits<ReturnType (ClassType::*)(Arguments...)> : function_traits<ReturnType (*)(Arguments...)>
{
};

// Callback wrapper that represents all Types of callbacks (type erasure)
struct CallbackWrapper
{
    template <typename T>
    // Template Metaprogramming
    CallbackWrapper(T &&obj) : wrappedCallback(
                                   std::make_unique<Wrapper<typename std::remove_reference<T>::type>>(std::forward<T>(obj)))
    {
    }

    // -> Operator overload for function calls
    // first overload for verifying the typing
    bool operator()(const std::type_info &type) const
    {
        return (*wrappedCallback)(type);
    }
    // second overload for calling the callback itself
    void operator()(const std::any &data)
    {
        return (*wrappedCallback)(data);
    }

    struct CallbackBase
    {
        virtual bool operator()(const std::type_info &type) const = 0;
        virtual void operator()(const std::any &data) = 0;
        virtual ~CallbackBase() {}
    };

    // Base type that represents the callback function supported
    template <typename T>
    struct Wrapper : public CallbackBase
    {

        // Gets the argument of the first argument passed to Callback through this wrapper
        // Templated typedef:
        // Defintion of a type based on generic template. Since function_traits is generic, ::template keyword must be used
        // Furthermore, typename is used since the result type will also be generic
        // Alternative: typedef typename function_traits<T>::template arg<0> arg_type;
        // typedef typename T::template arg_type<0> argument;
        // /https://stackoverflow.com/questions/610245/where-and-why-do-i-have-to-put-the-template-and-typename-keywords

        //Note that the indexing ensures fix number of arguments
        using argument = typename function_traits<T>::template arg<0>;
        

        // constructor, pass object to template lambda function
        Wrapper(const T &t) : wrappedObject(t) {}

        // Verifies if type argument type matches
        bool operator()(const std::type_info &type) const override
        {
            // typeid will convert the typdef argument to type_info for comparison
            if (typeid(argument) == type)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        // call template lambda function by converting the type to arg_type
        void operator()(const std::any &data) override
        {
            wrappedObject(std::any_cast<argument>(data));
        }

        // Template lambda function
        T wrappedObject;
    };

    // Reference or pointer to function passed via the handler
    std::unique_ptr<CallbackBase> wrappedCallback;
};

#include <iostream>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
// Example of wrappers and tmp with producer/consumer example

std::queue<int> queue;

class ConsumerProducer
{

public:
    ConsumerProducer(){
        this->mx = new std::mutex();
        this->cv = new std::condition_variable();
    };
    ConsumerProducer(const ConsumerProducer&) = delete; 
    ~ConsumerProducer()
    {
        this->callbacks.clear();
        delete mx;
        delete cv;
    }
    template <typename T>
    void handle(T callback)
    {
        static_assert(function_traits<T>::arity <= 1, "Maximum one argument allowed");
        callbacks.push_back(callback);
    }

    void consume()
    {
        while (true)
        {
            const std::any msg = this->getMessages();

            for (CallbackWrapper &cb : this->callbacks)
            {
                // calls the bool operator to verify typing
                if (cb(msg.type()))
                {
                    // if true, call the callback
                    cb(msg);
                }
            }
        }
    }

    void producer()
    {
        while (true)
        {
            std::unique_lock<std::mutex> lock(*this->mx);
            queue.push(this->val++);
            cv->notify_one();
        }
    }

private:
    std::vector<CallbackWrapper> callbacks;
    int val = 0;
    std::mutex* mx;
    std::condition_variable* cv;
    std::any getMessages()
    {
        std::any msg;
        std::unique_lock<std::mutex> lock(*mx);
        cv->wait(lock, []()
                { return !queue.empty(); });

        msg = queue.front();
        queue.pop();

        return msg;
    }
};
#include <algorithm>

void internal_handler(int i){
    std::cout << "internal_handler" << std::endl;
}

int main()
{

    ConsumerProducer consumerProducer = ConsumerProducer();

    consumerProducer.handle([](int i){
        std::cout << i << std::endl;
    });

    consumerProducer.handle(&internal_handler);

    //Note that std::thread constructor invokes the copy constructor
    //Hence, std::ref internally creates a copyable object and provide reference to the object passed
    std::thread thread1(&ConsumerProducer::consume, std::ref(consumerProducer));
    std::thread thread2(&ConsumerProducer::producer, std::ref(consumerProducer));

    thread1.join();
    thread2.join();

    return 0;
}


//FOR INTER-PROCESS COMMUNICATION:
//https://betterprogramming.pub/c-framework-for-inter-process-message-passing-df3789f982bc