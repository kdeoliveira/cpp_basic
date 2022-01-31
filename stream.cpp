#include <iostream>
#include <string>
#include <sstream>

using namespace std;


int main(){
    string mystr = "Provide a string: ";
    int val;

    cout << mystr;
    getline(cin, mystr);    // Gets entire input line
    cout << mystr << endl;
    cout << "Provide a number: ";
    getline(cin, mystr);
    stringstream(mystr) >> val; //Converts a stream object to another data type by deduction
    cout << val << endl;

    return 0;
}
