#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

/**
 * Similar to longest common sequence, given two strings it returns the longest consecutive matching sequence.
 * 
 */


std::vector<std::string::iterator> common_prefix(std::string s1, std::string s2){
    std::vector<typename std::string::iterator> _results;

    for(auto x = s1.begin(), y = s2.begin(); x != s1.end() && y != s2.end(); ++x, ++y){
        if(*x != *y) break;
        _results.push_back(x);
    }
    
    return _results;
}


int main(void){

    std::vector<std::string::iterator> x = common_prefix("KevindeOliveira", "KevOliveira");


    for(auto e : x){
        std::cout << *e;
    }

    std::cout << std::endl;

    return 0;
}