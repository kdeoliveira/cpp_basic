//Multithreading example with Producer-Consumer


// std::mutex m_mutex;
// void mutexes(){
    // std::unique_lock ul(m_mutex);
    // critical data sharing
    // m_mutex.unlock();
    // non critical data
    //out of scope unlocks automatically
// }


#include <mutex>
#include <thread>
#include <stdio.h>
#include <iostream>
#include <condition_variable>

//Note that the below data types can be implemented on the object that will be mutually shared between threads
//Condition variable allows wait and notify signals between threads
std::condition_variable m_cd;
std::mutex m_mutex;
//Mutually exclusive data
bool g_ready = false;
// int* buffer = new int[4];
int buffer = 0;

void consumer(){
    while(true){
        //The thread accessing this section will lock entrance for any other thread trying to access the same section
        std::unique_lock<std::mutex> ul(m_mutex);
        //Wait on condition variable to be notified
        //Optional lambda expr: condition variables also checks if return value is true after being notified
        m_cd.wait(ul, [&]{
            return g_ready;
        });

        // std::cout << buffer[0] << buffer[1] << buffer[2] << buffer[3] << std::endl;
        std::cout << buffer<< std::endl;
        buffer = buffer % 5;
        g_ready = false;

        //Notify the condition variable to release mutex
        m_cd.notify_one();
    }
}


void producer(){
    while(true){
        std::unique_lock<std::mutex> ul(m_mutex);
        buffer++;
        g_ready = true;
        m_cd.notify_one();


        //Consumer has been notified and it's consuming data; Then wait until consumption has been finished
        //Alternatively, a second condition_variable can be created
        m_cd.wait(ul, [&]{
            return g_ready == false;
        });
    }
}


int main(){

    std::thread t1(consumer);
    std::thread t2(producer);

    t1.join();
    t2.join();

    return EXIT_SUCCESS;
}

