#include <iostream>
#include <stdlib.h>
#include <fstream>

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        std::cout << "incorrect number of parameters provided" << std::endl;
        std::exit(1);
    }

    std::fstream file; // file stream for reading and writing files
    
    char* data = new char[10];

    file.open(*(argv + 1), std::ios::in | std::ios::out | std::ios::trunc); // in | out allows the file stream to have R/W access and creating output file


    std::cout << "Writing into file " << std::endl;
    std::cin.getline(data, 10);
    std::cin.ignore(1);

    file << data << std::endl; //Writes the value from cin to file


    file.seekg(1,std::ios::end);    //File position pointer: allows to modify the current position of the position pointer
                        // 1-byte from the end of the file
                        // seekg: For reading
                        // seekp: For writing

    std::cout << "File has be written with the value:" << std::endl;
    file >> data;
    std::cout << data << std::endl;


    file.close();
    return 0;
}