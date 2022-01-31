#include <iostream>
#include <string>

using namespace std;

string name = "Basics of c++";

// if NEWLINE is not define; then define it
#ifndef NEWLINE
    #define NEWLINE <<endl //Preprocessor constant: single line instruction whose directive is replaced before compiled time
#endif

using WORD = string; // Type aliasing

// Preprocessor, directive processed before compilation
#ifndef MIN
    #define MIN(a,b) (( (a) < (b) ) ? a : b)
#endif

#define TEST 1

#ifdef TEST //Code below is only defined if TEST has been defined
    int b;
    int a = (b = 3, b + 2); // Given b=3, then a = b + 2
#endif

#if 0   //Any code below will be commented out
    Comment section of preprocessors
#endif

#define CONCAT (x, y) x ## y // preprocessor returns the concatanation of x and y; not that the concatanation xy may be used a new variable

int foo {10};
decltype(foo) bar;  //Type Deduction:
                    // bar is declared of same type of foo
                    // Alternative: auto bar = foo



int main(){

    cout << "File name: " << __FILE__ <<endl; //Predefined macro that provides current file name

    WORD str = "Kevin";
    cout << str <<endl;

    cout<< name << endl;
    cout << foo << " and " << bar NEWLINE;

    cout << a NEWLINE;

    //Preprocessor function call
    cout << MIN(3,4) NEWLINE;

    cout << "End of program";

    return 0;
}