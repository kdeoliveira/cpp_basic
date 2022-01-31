#include <iostream>

using namespace std;

//namespace
namespace myNamespace{
    const double x = 3.1416;
}


//passed by value
int doub(int a){
   a*=2;
   return a; 
}

//passed by reference
int doub2(int& a){
    a*=2;
    return a;
}

//passed by reference - immutable
int doub3(const int& a){
    return a*2;
}


// Template Function
template <class T>
T sum(T a, T b){
    return a + b;
}

int main(){

    //namespace: value defined in myNamespace scope
    cout << myNamespace::x<<endl;

    int x = 2;
    cout << doub(x) << "\t" << x << endl;
    cout << doub2(x) << "\t" << x << endl;

    //Calling generic template function
    cout << sum<int>(2,6) <<endl;

    return 0;
}