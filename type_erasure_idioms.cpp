#include <stdio.h>

#include <utility>

// Type erasure: templates with polymorphism for class wrappers

// Class wrappers: Wrap set of class that shares a common interface (method) but are not tied to a base class
// The wrapper will serve as an interface (as in java) for such objects that perform the common functionality

//lvalue: any object that occupies a location in memory (can be modified directly)
//rvalue: any object that is not stored or have reference in memory (canNOT be modified directly)


//Main class wrapper that encapsulates and hide all type erasure implementation

#include <memory>

class MainWrapper{
    public:
        template<typename T>
        //Removes any reference passed via T (const, &, pointers, ...)
        //Gets/Deduce the type of _wrapped and forwards to template T
        MainWrapper(T&& _wrapped) : wrapped_object{
            std::make_unique<WrapperCase<typename std::remove_reference<T>::type>>( std::forward<T>(_wrapped) )} {}
        MainWrapper() = delete;

        void execute_fn() {
            return this->wrapped_object->execute_fn();
        }


    private:
        //Type erasure concept which holds the common implementation among classes
        class BaseCase{
            public:
                virtual void execute_fn() const = 0;
        };

        //Type erasure model which implements the typing (template) and forwards to the BaseCase
        template<typename T>
        class WrapperCase : public BaseCase{
            private:
                T object;
            public:
                WrapperCase(const T& _object) : object{_object}{}
                const void execute_fn() const {
                    return this->object->execute_fn();
                }

                WrapperCase() = delete;

        };

        std::unique_ptr<BaseCase> wrapped_object;


};









//Concrete classes with no Base Class 
//All share common function void execute_fn()

class A{

    public:
        void method_of_a(){
            puts("particular function of A");
        }
        void execute_fn(){
            puts("execute fn function");
        }
};

class B{

    public:
        void method_of_b(){
            puts("particular function of B");
        }
        void execute_fn(){
            puts("execute fn function");
        }
};

class C{

    public:
        void method_of_c(){
            puts("particular function of C");
        }

        void execute_fn(){
            puts("execute fn function");
        }
};


#include <cstdlib>

int main(){


    return EXIT_SUCCESS;
}