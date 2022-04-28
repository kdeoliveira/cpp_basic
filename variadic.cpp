

#include <cstdlib>

#include <iostream>

// There is two ways (1 - Function template and 2 - Class template) of implementing recursive variadic templates:

// 1 - Function template
//     (Base case): Provide a one-template definition with the actual behavior of the object
//     (Recursive Case): Call the base case with one argument and recursively call itself with the rest of the args

// Base case/struct definition
template<typename T>
void print(T t){
    //Fallback call (function called for one argumnet)
    std::cout << t << " " << typeid(t).name() << std::endl;
}

// Recursive case/struct
// ...K: accepts 0 or more K templates
template<typename T, typename... K>
void print(T t, K...k){
    //Calls the recursive case with expanded list of arguments
    print(k...);

    //Calls the base case recursively
    print(t);
}



// 2 - Class template
//     (Base Case): Provides a type definition only for the actual implementation of the object
//     (Recursive Case): Actual implementation that recursively calls itself with the expanded rest arguments

//Base case; in this scenario this struct serves only as type definition for the recursive case. No implementaion required here
template<typename...T>
struct Tuple{};

//Recursive case
template<typename T, typename...R>
struct Tuple<T, R...> : public Tuple<R...>{
    Tuple() : Tuple<R...>(){}
    //Gets first arg passed and save to tail; Then recursively call Tuple constructor with the remaining arguments
    Tuple(T t, R... r) : Tuple<R...>(r...), tail(t){}

    //Only the last recursive call argument will be stored inside tail
    //Note that Tuple arguments are called in the reverse order
    T tail;
};

int main(){

    std::cout << "Function template ====" << std::endl;
    print("char", 12, 123.1f, 456.5);

    std::cout << "Class template ====" << std::endl;
    Tuple<int, const char*, float> tp(12, "fdsfs", 121.5f);

    std::cout << tp.tail << std::endl;

    return EXIT_SUCCESS;
}