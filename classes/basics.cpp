#include <iostream>
using namespace std;


namespace basics{   //Provides namespace for the enclosing definitions
    class A{
        private:
            int x, y;
        public:
            A();
            A(int, int);
            A(const A&); //Copy constructor (must be defined if the class has a data member as pointer)
            ~A();
            int total();
            int getX() const;   //const function: If ocject is const, then getX() is allowed to be called
            const int& getX();  //returns a const value of X

            inline static int size{0}; //static data member, which is common to all objects of this class; Inline: remnove overhead of function (only applicable to short function)

            friend void printPositions(A);   //Function is defined outside the scope of the class but have access to all data members of this class; including privates



    };

    //member initialization
    A::A() : x{5}, y{5}{
        size++;
    }
    A::A(int x, int y){
        this->x = x;
        this -> y = y;
        size++;
    }
    A::A(const A& obj){
        this->x = obj.x;
        this->y = obj.y;
    }
    A::~A(){
        cout << "Destructor caleld" << endl;
    }

    int A::total(){
        return (this->x + this->y);
    }
    int A::getX() const{
        return x;
    }
    const int& A::getX(){
        return x;
    }

    void printPositions(A a){
        //Access to private members of A
        cout << a.x << a.y  << endl;
    }
}

int main(){
    basics::A::size = 0;
    basics::A first = basics::A(2,3);
    basics::A second = basics::A();

    basics::A* foo = &first;

    cout << first.total() <<endl;
    cout << first.getX() <<endl;
    cout << second.total() <<endl;
    //Arrow operator
    cout << foo->total() <<endl;

    cout << "Total call of static size: " << basics::A::size << endl;


    printPositions(first);
}

