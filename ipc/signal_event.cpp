

#include <cstdlib>
#include <csignal>

#include <iostream>
#include <unistd.h>
#include <sys/types.h>

// Process that generates the signal

void signalHandler(int signum, siginfo_t *args, void *)
{
    // 0: send to every process in the process group of the calling process
    // negative numbers: send to the equivalent processes process group ID
    // note that for now, the pid must be gotten before running this process
    

    if(signum == SIGUSR1){
        std::cout << "Signal Handler" << std::endl;

        kill(args->si_value.sival_int, SIGUSR1);
    }
  
    
}

int main()
{
    int parent = getpid();
    // Creates a child process over this application
    pid_t pid = fork();

    if (pid == 0)
    { // Then current process is the child porocess


        std::cout << "Chlid: " <<  pid << std::endl;

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

    

    }
    else    //This is the parent process
            //Note that pid_t pid now holds the actual
    {
        std::cout << "Parent: " << pid << std::endl;


        // set signal action structure
        struct sigaction sa;
        sa.sa_sigaction = &signalHandler;
        sa.sa_flags = SA_SIGINFO;
        
        

        sigemptyset(&sa.sa_mask);

        // register signal
        sigaction(
            SIGUSR1, &sa, nullptr);
        


        try
        {
            // send signal to this process
            // int status = kill(pid, SIGUSR1);
            sigval val;
            val.sival_int = (int) pid;

            //Force parent process to sleep so child process can execute first
            sleep(3);

            if(sigqueue(parent, SIGUSR1, val) < 0){
                perror("EPERM");
            }
        }
        catch (...)
        {
        }


    }
    return 0;

}