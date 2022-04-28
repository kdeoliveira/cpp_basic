#include <iostream>


// Copy assignment: https://stackoverflow.com/questions/4172722/what-is-the-rule-of-three
// 

namespace basics{   //Provides namespace for the enclosing definitions
    class A{
        private:
            int x, y;
        public:
            A();
            A(int, int);
            // Some resources cannot or should not be copied, such as file handles or mutexes. Hence, in no presence of copy constructor the default constructor is called
            // Note that copy assignment and copy/move consturctor should be explicitly declared if the class is to acquire a resource (pointer, another object, file) - Class Wrappers or RAII idioms
            A(const A& _x) : x{_x.x}, y{_x.y}{
                //Use std::copy if passing STL with iterators
            }
            A& operator=(A x){
                swap(*this, x);
                return *this;
            }
            //Move assignment
            A& operator=(A&& x){
                swap(*this, x);
                return *this;
            }
            A(A&& _x) noexcept : A(){   //move constructor; should generally include noexcept
                swap(*this, _x);
            }

            //Copy and swap idiom for copy/assignment
            //https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
            friend void swap(A& first, A&second){
                // It uses ADL to do an unqualified call to any overloaded definition of swap (std::swap, or other swap defined in this namespace)
                //https://stackoverflow.com/questions/8111677/what-is-argument-dependent-lookup-aka-adl-or-koenig-lookup
                using std::swap;
                //Effectively swipe data members of both objects
                swap(first.x, second.x);
                swap(first.y, second.y);
            }

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
        std::cout << "Destructor caleld" << std::endl;
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
        std::cout << a.x << a.y  << std::endl;
    }
}

int main(){
    basics::A::size = 0;
    basics::A first = basics::A(2,3);
    basics::A second = basics::A();

    basics::A* foo = &first;

    std::cout << first.total() <<std::endl;
    std::cout << first.getX() <<std::endl;
    std::cout << second.total() <<std::endl;
    //Arrow operator
    std::cout << foo->total() <<std::endl;

    std::cout << "Total call of static size: " << basics::A::size << std::endl;


    printPositions(first);
}

