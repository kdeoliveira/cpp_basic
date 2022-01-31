


#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <iostream>


int main(int argc, char *argv[]){

    char c;
    int fd;

                //getopt: parse options paramters passed to command line until no character is found (-1)
                // + : option processing stops as soon as a nonoption argument is encountered

    while((c) = getopt(argc, argv, "+phv") != -1){
        switch (c)
        {
        case 'p':
            std::cout << "Selected -p" << std::endl;
            break;
        
        default:
            break;
        }
    }
    
    //Note that optind is a global variable
    std::cout << "Last index of options argv" << optind << std::endl;

    return EXIT_SUCCESS;
}