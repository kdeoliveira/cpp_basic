

#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <error.h>
#include <memory>
#include <string>

template<typename T>
class Runnable{
    public:
        virtual T run() = 0;
        virtual ~Runnable(){};
};

template<typename T>
class Thread{
    public:
        Thread(std::shared_ptr<Runnable<T>> run, bool isDetached = false);
        Thread(std::shared_ptr<Runnable<T>> run, bool isDetached, int policy, int priority);
        //Requires shared_ptr; could use shared_ptr::reset() to pass ptr ownership to raw ptr
        Thread(Runnable<T>*, bool);
        Thread(const Thread&);
        const Thread& operator=(const Thread&);

        virtual ~Thread();
        void start();
        void join();
        T getResult(){
            return (this->m_result);
        }


        // virtual void* run();
        // static void* startThreadRunnable(void* arg);
        // void printError(char* msg, int status, char* fileName, int lineNumber);

    private:
        pthread_t m_thread_id;
        bool detached;
        bool completed;
        T m_result;
        pthread_attr_t m_thread_attr;
        struct sched_param m_thread_params;
        std::shared_ptr<Runnable<T>> m_runnable;
        static void* startThread(void* arg);

};

template<typename T>
Thread<T>::Thread(std::shared_ptr<Runnable<T>> run, bool isDetached) : m_runnable{run}, detached{isDetached} {
    if(!m_runnable.get()){
        throw "Runnable object is NULL";
    }
}
template<typename T>
Thread<T>::Thread(Runnable<T>* run, bool isDetached) : detached{isDetached}{
    //Pass ownership to this pointer
    m_runnable.reset(run);
}
template<typename T>
Thread<T>::Thread(std::shared_ptr<Runnable<T>> run, bool isDetached, int policy, int priority) : m_runnable{run}, detached{isDetached}{

    pthread_attr_setinheritsched(&m_thread_attr, PTHREAD_EXPLICIT_SCHED);
    int status = pthread_attr_setschedpolicy(&m_thread_attr, policy);
    if(status) throw "Invalid schedule policy";
    m_thread_params.sched_priority = priority;
    status = pthread_attr_setschedparam(&m_thread_attr, &m_thread_params);
    if(status) throw "Invalid schedule policy";
}

template<typename T>
Thread<T>::~Thread(){
    pthread_attr_destroy(&m_thread_attr);
}
template<typename T>
void* Thread<T>::startThread(void* arg){
    
    //Casting the thread passed through args
    Thread* current_thread = static_cast<Thread*>(arg);
    if(current_thread == nullptr) throw "Thread passed through argument is invalid";
    current_thread->m_result = current_thread->m_runnable->run();
    current_thread->completed = true;
    return static_cast<void*>(&current_thread->m_result);
}

template<typename T>
void Thread<T>::start(){
    int status = pthread_attr_init(&m_thread_attr);
    if(status)  throw "Error when init thread attr";

    status = pthread_attr_setdetachstate(&m_thread_attr, detached ? PTHREAD_CREATE_DETACHED : PTHREAD_CREATE_JOINABLE);
    if(status)  throw "Error when init thread attr";

    //Note that this Thread object is passed to startThread function as args
    //This would be not necessary is startThread is defined as non-static
    status = pthread_create(&m_thread_id, &m_thread_attr, Thread::startThread, (void *) this);
    if(status)  throw "Error creating thread";
}
template<typename T>
void Thread<T>::join(){
    if(!detached){
        int status = pthread_join(m_thread_id, nullptr);
        if(status) throw "Unable to join this thread";
    }
}


class runnable : public Runnable<std::string>{
    public:
        virtual std::string run(){
            int i = 0;
            while(true){
                std::cout << "Running the thread" << std::endl;
                if(i > 10)  break;
                i++;
            }
            return "Teste";
        }
        virtual ~runnable(){

        }
};

class thread : public Thread<std::string>{
    public:
        thread(int id, std::shared_ptr<Runnable<std::string>> runn) : m_id(id), Thread{runn, false}{}
        thread(int id, Runnable<std::string>* runn) : m_id(id), Thread{runn, false}{}
        

    private:
        int m_id;
};


int main(){
    //Note that shared object should implement synchronization
    try{

    // std::shared_ptr<Runnable> runn(new runnable()); //alternative to make_shared
    Runnable<std::string>* runn = new runnable();
    std::unique_ptr<thread> thread1 = std::make_unique<thread>(123, runn);

    thread1->start();
    thread1->join();


    std::cout << "Thread has joined with value: " << thread1->getResult() << std::endl;
    
    }catch(const char *e){
        std::cout << e << std::endl;
    }

    
    return EXIT_SUCCESS;
}