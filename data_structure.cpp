    #include <exception>
#include <stdlib.h>
#include <initializer_list>
#include <type_traits>

template<typename T>
class CustomVector{
    private:
        T* element;
        int sz;

    public:
    CustomVector(){
        this->sz = 0;

    };
        explicit CustomVector(int size){
            if(size < 0)
                throw "Out of Range";
            this->element = new T[size];
            this->sz = size;
        }

        ~CustomVector(){
            delete[] element;
        }

        //Operator overloads
        T& operator[](int i){
            if(i < 0 || i > sz){
                throw "Out of Range";
            }
            return element[i];
        }
        const T& operator[](int i) const{
            if(i < 0 || i > sz){
                throw "Out of Range";
            }
            return element[i];
        }

        //Function call operator overload
        bool operator()(const T& x){
            this->element[++this->sz] = x;
            return true;
        }
        constexpr int size() const{
            return this->sz;
        }

        //Support for range-for loop
        T* begin(CustomVector<T> &x){
            return x.size() ? &x[0] : nullptr;
        }
        T* end(CustomVector<T>& x){
            return x.begin() + x.size();
        }

        //Loops over the iterator pointers to verify if the value exists
        //std library: find(begin(), end(), x)
        bool has(T x){
            for(auto p = this->begin(); p != this->end(); p++)
                if(*p == x)
                    return true;

            return false;
        }

        //Variadic arguments with type verification of generic typenames
        template<typename ...K>
        void push_back(K... args){
            auto temp = {args...};

            for(auto& k : temp){
                this->element[++this->sz] = k;
            }
        }


};








int main(){
    CustomVector<int> v;
    v.push_back(2,4,5,7,8);

    v[2];

    return EXIT_SUCCESS;
}