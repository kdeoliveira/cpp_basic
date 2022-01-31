

//http://www.qssl.com/developers/docs/6.4.0/neutrino/getting_started/s1_timer.html
//Timer object with pulse notification at every periodic time
//Pulse (SIGEV_PULSE): send message at every timer period
//Note that pulse is an implementation specific to Neutrino RTOS; Hence signal will be used instead


#include <time.h>   //-lrt library
#include <signal.h>
#include <cstdlib>
#include <signal.h>
#include <iostream>

static void setupTimer(void){

    timer_t timer;
    sigevent_t ev;
    ev.sigev_notify = SIGEV_SIGNAL; //SIGEV_THREAD for thread creation instead
    ev.sigev_signo = SIGALRM;

    //Value passed to notification to signal via siginfo_t*
    ev.sigev_value.sival_int = 10;
    
    
    

    //sets time source to time of the day's variable
    //CLOCK_MONOTONIC: constant clock source (cannot be changed)
    //CLOCK_SOFTTIME: allows device with periodic tasks to be turned off; clock source will be reset
    int timerid = timer_create(
        CLOCK_REALTIME, &ev, &timer
    );

    if(timerid == -1) exit(EXIT_FAILURE);

    //Set and start timer
    // 0: relative timer
    // 1: absolute timer
    itimerspec val;
    val.it_value.tv_sec = 2; //First phase of timer
    val.it_value.tv_nsec = 0;
    val.it_interval.tv_sec = 2; //Period of timer
    val.it_interval.tv_nsec = 0;
    if( timer_settime(
        timer, 0, &val, nullptr
    ) == -1)
        std::cout << "Error when setting timer\n";


}
// if signal handler set on:
//      sigaction.sa_handler -> void f(int)
//      sigaction.sa_sigaction -> void* f(int, siginfo_t*, void*); requires set sa_falgs to SA_SIGINFO
// For inter thread communication use kill()
void signalHandler(int signum, siginfo_t* args, void*){

    time_t now;
    time(&now);
    std::cout << "Signal of value " << args->si_value.sival_int << " has been raised at " << now << std::endl;
}


int main(int argv, char * argc[]){

    struct sigaction  sa;

    sa.sa_sigaction = &signalHandler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    //Sets the handler/action to the respective signum
    sigaction(
        SIGALRM, &sa, nullptr
    );

    
    //use kill to communicate with other process

    setupTimer();

    //In case of kill, use this set in order to wait for incoming signal
    // sigset_t set;
    // siginfo_t info;

    // sigemptyset(&set);
    // sigaddset(&set, SIGALRM);
    // sigprocmask(SIG_BLOCK, &set, nullptr);
    // sigwaitinfo(&set, &info);

    //While to get signal hanler calls
    while(true){
    }

    return EXIT_SUCCESS;
}

