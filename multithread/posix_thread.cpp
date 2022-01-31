#include <pthread.h>
#include <stdio.h>
#include <cstdlib>

#include <iostream>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//Note that void * is required to indicate any data type
void* workerMutex(void * args){

    int arg = *((int*) args);

    pthread_mutex_lock(&mutex);

    std::cout << "Worker Mutex called" << "Argument: " << arg << std::endl;

    pthread_mutex_unlock(&mutex);

    return 0;
}



pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int global = 0;
bool ready = false;

// Condition variables - signal and wait
void * producer(void * arg){
    pthread_mutex_lock(&mutex);

    global++;

    ready = true;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);

    return nullptr;
}
void * consumer(void * arg){

    pthread_mutex_lock(&mutex);
    //While serves as an additional condition beyond the condvar; In c++11 it uses lambda expression instead
    while(!ready) pthread_cond_wait(&cond, &mutex);

    std::cout << "Consumer: " << global << std::endl;

    pthread_mutex_unlock(&mutex);

    return nullptr;
}



int main(){
    pthread_t* thread = new pthread_t(123);
    

    pthread_attr_t attr;
    //Parameters of pthread so policy can be set
    struct sched_param params;

    //Initialize attr and sets attr to joinable
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    //Define pthread to be explicitly changed and set scheduling algorithm
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    params.sched_priority = 15;
    pthread_attr_setschedparam(&attr, &params);


    int* arg = new int(10);

    pthread_create(thread, 0, workerMutex, arg);



    //Barrier of synchronization; Block section of code until all pthreads have reached the pthread_barrier_wait call
    pthread_barrier_t barrier;
    //Init barrier with number of threads required to reach
    pthread_barrier_init(&barrier, nullptr, 1);


    pthread_barrier_wait(&barrier);
    
    
    std::cout << "All 2 threads have passed the barrier and may procceed" << std::endl;

    
    
    pthread_join(*thread, nullptr);


    pthread_t threadConsumer, threadProducer;
    //Consumer-producer
    pthread_create(&threadConsumer, 0, producer, nullptr);
    pthread_create(&threadProducer, 0, consumer, nullptr);

    pthread_join(threadConsumer, 0);
    pthread_join(threadProducer, 0);

    //Note that the mutexes must be destroyed in the Destructor
    pthread_mutex_destroy(&mutex);
    pthread_barrier_destroy(&barrier);

    return EXIT_SUCCESS;
}



// pthread_create return type ->
//              EAGAIN: Insufficient system resources to create thread.
//              EFAULT: An error occurred trying to access the buffers or the start_routine provided.
//              EINVAL: Invalid thread attribute object attr.
//              EOK: Success.


// pthread type ->
//              PTHREAD_CREATE_DETACHED: Main thread doesnt care about this thread termination; a pthread_exit should be called or call pthread_detach() on thread
//              PTHREAD_CREATE_JOINABLE: Main thread can be join this thread for common termination 


