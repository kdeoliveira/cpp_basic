



#include <pthread.h>
#include <cstdlib>
#include <semaphore.h>
#include <iostream>

//Semaphore is mostly used when shared data can be accessed by multiple threads at the same time
//Note that for binary semaphore, it provides an equivalent effect of condvars
sem_t sem_producer, sem_consumer;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


#define BUFFER_SIZE 10
int buffer[BUFFER_SIZE];
int index_producer = 0;
int index_consumer = 0;

void* producer(void*){

    while(true){
        // If semaphore count = 0: Thread waits
        // If semaphore count > 0: Thread continues and count is decremented by 1
        sem_wait(&sem_producer);

        pthread_mutex_lock(&mutex);
        buffer[index_producer] = index_producer;
        index_producer = (index_producer + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);


        //Increment semaphore count by 1  and wake up any waiting thread
        sem_post(&sem_consumer);
    }
}

void* consumer(void*){
    while(true){

        sem_wait(&sem_consumer);

        // Note that mutex is still implemented so race condition between both threads does not occur at this section; One access per thread at the time
        //Locking and unlocking must be done close to avoid deadlock
        pthread_mutex_lock(&mutex);
        std::cout << "Consumer buffer[" << index_consumer << "]: " << buffer[index_consumer] << std::endl;
        //Remove value as it has been consumed
        buffer[index_consumer] = 0;
        index_consumer = (index_consumer + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);


        sem_post(&sem_producer);
    }
}

int main(){
    //Initialize semaphore; 0: private to process; count of (int) n

    //sem_producer: Used in producer so thread can access critical section until buffer is completly full
    sem_init(&sem_producer, 0, BUFFER_SIZE);
    //sem_consumer: Used in consumer so thread can only access if data is present (one at the time)
    sem_init(&sem_consumer, 0 , 0);


    pthread_t threads[2];
    pthread_create(&threads[0], nullptr, consumer, nullptr);
    pthread_create(&threads[1], nullptr, producer, nullptr);


    pthread_join(threads[0], nullptr);
    pthread_join(threads[1], nullptr);

    
    sem_destroy(&sem_producer);
    sem_destroy(&sem_consumer);
    pthread_mutex_destroy(&mutex);
    return EXIT_SUCCESS;
}