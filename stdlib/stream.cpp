#include <cstdlib>

#include <vector>
#include <iterator>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>



int main(int argc, char* argv[]){


    //Output stream iterator of type string that points to std::cout
    //Hence, any std::string passed to this iterator will also point to std::cout
    std::ostream_iterator<std::string> output {std::cout};

    *output = "Test of iterator streams";
    output++; //move to next element
    *output = ": [any key] ";


    //Input stream iterator of type string that points to std::cin
    std::istream_iterator<std::string> input{std::cin};
    // input++;








    //Stream iterator for files
    //Reads one file and write a sorted and unique copy of its content to another
    std::string from, to;

    std::cout << "Type files name: ";
    std::cin >> from >> to;



    std::ifstream input_file {from}; 
    std::istream_iterator<std::string> input_file_iterator {input_file};
    //Indicates where input termination (sentinel). Note that it must be provided for inputs comparison
    std::istream_iterator<std::string> end_of_stream{};


    std::ofstream output_file {to};
    std::ostream_iterator<std::string> output_file_iterator {output_file};
    

    std::vector<std::string> _temp {input_file_iterator, end_of_stream};
    std::sort(
        _temp.begin(), _temp.end()
    );

    //Note that unique_copy would require a pointer to the place where the copy should start
    std::unique_copy(
        _temp.begin(), _temp.end(), output_file_iterator
    );

    if(
        !input_file.eof() || !output_file
    ){
        std::cout << "Error when reading files" << std::endl;
    }





    return EXIT_SUCCESS;
}