#include <csignal>
#include <iostream>

// SIGABRT: when abort() is called
// SIGFPE:  throw mathematical excpetion
// SIGIL:   throw illegal instruction exception
// SIGINT: (ctrl + c) signal
// SIGSEGV: access error
// SIGERM:  termination of program 

#ifdef _WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

void signalHandlerInt(int signum){
    std::cout << "Interrupt the signal " << signum << std::endl;
    exit(0);
}

int main(){
    int i{0};

    //Signal handler must be registered
    signal(SIGINT, signalHandlerInt);

    while(true){
        std::cout<< "Running..."<<std::endl;
        sleep(1);
        

        //raise manually a signal
        if(i == 3)  raise(SIGINT);

        i++;
    }

    return 0;
}