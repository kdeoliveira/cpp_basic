

#include <iostream>

int main(int argc, char* argv[]){

    if(argc != 1) exit(1);

    std::cout << "Process exec executing: " << argv[0] << std::endl;

    return 0;
}