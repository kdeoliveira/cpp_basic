#include <iostream>
using namespace std;

/*

*: deference operator (value-of)
&: reference operator (address-of)

*/

//Passing function as argument to another function as pointer
int addition(int a, int b){
    return a+b;
}

// Pointer to functions
int operation(int a, int b, int (*T)(int, int)){
    //T represents the function value passed; equivalent to callbacks or array function (lambda)
    //Note that only function requiring the same args is allowed
    return (*T)(a,b);
}


int main(){
    char x[] = "Kevin";
    char* ptr = nullptr;

    //dynamic memory allocation
    char* foo = new (nothrow) char[5];

    foo = x;

    cout << "foo: "<< *foo << endl;
    
    
    


    //Pointer variable don't need to be referenced (&)
    ptr=&x[0];

    cout << *ptr << " " << *(++ptr) << " " << *(++ptr) << " " << *(++ptr) << " " << *(++ptr) << endl;

    cout << operation(2,3,addition) << endl;

    return 0;
}
