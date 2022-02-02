#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstring>
#include <cstdlib>

#include <limits.h> //PIPE_BUF


// Unidirectional communication link between processes


int main(){

    int fd[2];

    char str[] = "kevin\0";

    pid_t pid;

    //Creates pipe 
    //fd[0]: read end of pipe
    //fd[1]: write end of pipe
    //in case of flags, use pipe2 --- O_DIRECT: write() executed in packet mode with buffer size set to PIPE_BUF bytes
    if( pipe(fd) == -1 ){
        perror("pipe");
        return EXIT_FAILURE;
    }

    //Creates a copy child process 
    // 0 -> Child running
    // + -> Parent running and val = child pid
    pid = fork();

    if(pid < 0){
        perror("fork");
        return 1;
    }

    // ==> Note on file descriptor of pipes <==
    // If a process attempts to read from an empty pipe, then read(2)
    // will block until data is available.  If a process attempts to
    // write to a full pipe (see below), then write(2) blocks until
    // sufficient data has been read from the pipe to allow the write to
    // complete

    //child process
    if(pid == 0){
        //Close read end for child process
        close(fd[0]);

        write(fd[1], str, strlen(str));

        close(fd[1]);

        //_exit: only exit this process
        _exit(EXIT_SUCCESS);
        
        
    }else{

        //Close write end of pipe
        close(fd[1]);
        char rcv;

        // PIPE_BUF: Read max number of bytes at once
        // read(fd[0], rcv, PIPE_BUF);
        //Alternative:
        while(read(fd[0] , &rcv, 1) > 0){
            write(STDOUT_FILENO, &rcv, 1);
        }
        //Note that STDOUT must contain a EOF marker at the end (alternatve: \0)
        write(STDOUT_FILENO, "\n", 1);

        //close read end of pipe
        close(fd[0]);

        //Wait on child's process to exit program
        //exit status of child passed to status variable
        int status;
        waitpid(pid, &status, 0 );

        if(!WIFEXITED(status) || !WEXITSTATUS(status))
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}