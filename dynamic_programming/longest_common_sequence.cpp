#include <string>
#include <vector>
#include <algorithm>

#include <iostream>


/**
 * Longest matching sequence of elements obtained from the two lists non consucitively
 */

int lcs(std::string s1, std::string s2){
    
    std::vector<std::string::iterator> _equal_seq;
    
    int m = s1.length(), n = s2.length();

    std::vector<std::vector<int>> lookup (m+1, std::vector<int>(n+1, 0) );
  
    // fill the lookup table in a bottom-up manner
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            // if the current character of `X` and `Y` matches
            if (s1[i - 1] == s2[j - 1]) {
                lookup[i][j] = lookup[i - 1][j - 1] + 1;
            }
            // otherwise, if the current character of `X` and `Y` don't match
            else  {
                lookup[i][j] = std::max(lookup[i - 1][j], lookup[i][j - 1]);
            }
        }
    }
 
    // LCS will be the last entry in the lookup table
    return lookup[m][n];

}










int main(){


    std::cout << lcs("OtSUtXkEDqSOYo", "fbiNbSjyFGXofbuNXG");

    return 0;

}