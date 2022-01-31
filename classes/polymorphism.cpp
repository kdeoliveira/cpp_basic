#include <iostream>
using namespace std;
#include <string>
//Abstract class or Interface
class A{
    protected:
        int width, height;
    public:
        A() : width{2}, height{2}{}
        void set(int a, int b){
            width=a;
            height=b;
        }
        virtual string toString(){  //simple virtual function allows the child class to reimplement it
            return to_string(width*height);
        }

        virtual int area() = 0; //pure virtual function
};

class B: public A{
    public:
        B(){}
        //Prevents implicit conversion and assignment-like opertion on object; Ideal when polymorphism is used to prevent wrong auto conversion by the compiler
        //Explicit disable copy-initialization: B b = a() returns an error
        explicit B(const A& x){
            width = 0;
            height = 0;
        }
        
        int area(){
            return width*height;
        }

        //Overides the funciton of the Base class        
        string toString() override{
            return "null";
        }
};

int main(){

    //Polymmorphism is used through pointers

    A* a = new B();
 

    a->set(5,5);

    cout << a->area() << endl;

    cout << a->toString() << endl;


    delete a;
     

}

