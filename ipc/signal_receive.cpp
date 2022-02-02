
#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <pthread.h>



// Alternative for signal events using a second program
//Process that listens to a signal event

int main(){


    setgid(113792);
    
    std::cout << getpid() << std::endl;
    


    sigset_t set;
    siginfo_t info;

    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    //Set this process in SIG_BLOCK state
    //Any signal received by this process will be ignored; Hence use sigwaitinfo to get the occurance
    sigprocmask(SIG_BLOCK, &set, nullptr);

    //Wait on blocking signal event
    sigwaitinfo(&set, &info);

    std::cout << info.si_signo << " " << info.si_code << " " << info.si_value.sival_int << std::endl;


    return 0;
}