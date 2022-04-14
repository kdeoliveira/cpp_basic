#include <cstdlib>
#include <list>
#include <vector>
#include <algorithm>

// Note on iterators:
// std::fn(begin_iterator, end_iterator, current_iterator)
// ===============
// If forward iterator provided, function will iterate forward from current
//      begin()  -> first element
//      end()    -> last element
// If reverse iterator provided, then iterate backward
//      rbegin() -> for reverse order; last element
//      rend() -> for reverse order; first element

// iterator::base() -> converts a reverse iterator to a forward iterator
//                     so, if the iterators provided were reversed, the std function will actually iterate forward

// Note on functions with predicators:
// If forward iterations:
//      From current_iterator interates forward through [begin_iterator, end_iterator]
// If reverse iterations:
//      From r_current_iterator interates background through [r_begin_iterator, r_end_iterator]



template<typename T>
std::list<T> sort_unique_element(std::list<T> in){

    //NOTE: std::set provides the same behavior as implemented in this function
    //Instead, could execute a std::copy to a set

    std::list<T> _result;

    std::sort(
        in.begin(),
        in.end()
    );

    // Removes adjacent duplicates in container from [firt, last)
    // Predicate (const Type& x, const Type& y) -- elements inside the container
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



// Find All Occurrences of implementation
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


#include <string>
// Erase any space located either left of right and returns the actual string
std::string ltrim(const std::string &str) {
    std::string s(str);

    s.erase(
        s.begin(),
        std::find_if(s.begin(), s.end(), not1(std::ptr_fun<int, int>(isspace)))
    );

    return s;
}

std::string rtrim(const std::string &str) {
    std::string s(str);

    s.erase(
        std::find_if(s.rbegin(), s.rend(), not1(std::ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}


int main(int argc, char* argv[]){



    return EXIT_SUCCESS;
}