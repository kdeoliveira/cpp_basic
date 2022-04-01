#include <cstdlib>
#include <list>
#include <vector>
#include <algorithm>


// Removes adjacent duplicates in container from [firt, last)
// Predicate (const Type& x, const Type& y) -- elements inside the container

template<typename T>
std::list<T> sort_unique_element(std::list<T> in){

    //NOTE: std::set provides the same behavior as implemented in this function
    //Instead, could execute a std::copy to a set

    std::list<T> _result;

    std::sort(
        in.begin(),
        in.end()
    );

    std::unique_copy(
        in.begin(),
        in.end(),
        //Pointer to the last element of a container that accepts push_back()
        std::back_inserter(_result)
    );

    return _result;
}


// Check if container has a given element
template<typename T, typename K>
bool has_val(const std::list<T>& container, const K& value){
    using arg = typename std::list<T>::value_type;
    static_assert(!std::is_same<arg , K>(), "Incorrect value passed");

    // std::find returns .end() iterator if not found
    return std::find(container.begin(), container.end(), value) != container.end();

}



// Find All implementation
// Checks all occurrence of an element in a given container and stores a poitner to its respective location
template<typename T> 
std::vector<typename std::list<T>::iterator> find_all(const std::list<T>& container, const T& element){
    std::vector<typename std::list<T>::iterator> _result;

    //Loop through the iterators (element's pointers instead)
    for(auto x = container.begin(); x != container.end(); ++x){
        if(*x == element){
            _result.push_back(x);
        }
    }

    return _result;
}





int main(int argc, char* argv[]){



    return EXIT_SUCCESS;
}