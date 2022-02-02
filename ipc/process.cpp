
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <string>

int main(int argc, char* argv[]){

    char c;
    char* arguments;
    //getopt: parse options paramters passed to command line until no character is found (-1)
    // + at the beginning : option processing stops as soon as a nonoption argument is encountered
    while((c = getopt(argc, argv, "phv")) != -1){
        
        switch (c)
        {
        case 'p':
            printf("Selected -p\n");
            break;
        case 'h':
            printf("Selected -h\n");
            break;
        case 'v':
            printf("Selected -v\n");
            break;
        default:
            break;
        }
    }

    //optind: global variable for the next non-optional args
    if(argv[optind] == nullptr) exit(EXIT_SUCCESS);

    arguments = argv[optind++];

    //Creates a child process that inherits this program
    //Note that locks, I/O fds and semaphores are not passed to child
    pid_t pid = fork();

    if(pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    //Child process
    if(pid == 0){
        
        printf("Child process exceuting: %u\n", getpid());

        //Note that argumnet sent to exec must contain NULL at the end to indicate EOF of argv
        char *argv_exec = "child";
        //Execute a new process and suspend this
        execlp(arguments, argv_exec, NULL);

        printf("Child process has finished execution\n");


        exit(EXIT_SUCCESS);

    }
    //Parent process
    else
    {
        printf("Parent process executing: %u\n", getpid());
        printf("Child process running under pid: %u\n", pid);

        //Wait on child's process (through its pid)
        //This process will be suspended until child's process changes state
        //Status of child process passed to variable status
        int status;
        if(waitpid(pid, &status, 0) > 0){
            if(WIFEXITED(status) && !WEXITSTATUS(status))   printf("child program exited successfully\n");
            else if(WIFEXITED(status) && WEXITSTATUS(status)){
              if(WEXITSTATUS(status) == 127)  printf("execv failed\n");
              else                            printf("child program exit failed\n");
            }else{
                printf("child program didn't terminated normally\n");
            }
        }else{
            perror("waitpid");
        }

        printf("Parent process has finished execution\n");

    }

    return EXIT_SUCCESS;
}