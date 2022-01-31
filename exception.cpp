#include <iostream>
#include <exception>
using namespace std;

class myexception : public exception{
    //Overriden function
    virtual const char* what() const throw(){
        return "My Exception Error";
    }
} myex;


int main(){
    try{
        throw myex;
    }
    catch(exception &e){
        cout << e.what() << endl;
    }
    return 0;
}