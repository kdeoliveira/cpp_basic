#include <iostream>
using namespace std;

//Generic template
template <class T = int> // =int provides a default typename in case no type is provided
class B{
    T value;
    public:
        B() : value{1}{}
        T getValue() const;
};

template <class T>
T B<T>::getValue() const{
    return value;
}


int main(){
    const B<int> x;
    cout << x.getValue() << endl;
}