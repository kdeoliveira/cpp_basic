






#include <string>
#include <vector>



/**
 * Given two list X and Y, return the shortest list Z possible such that both X and Y is a subsequence of Z
 * 
 * Note: U is subsequence of V iff U is contained in V non-consecutively
 */



int scs(std::string s1, std::string s2){

    int m = s1.length(), n = s2.length();

    std::vector<std::vector<int>> lookup (m+1, std::vector<int>(n+1, 0) );

    // initialize the first column of the lookup table
    for (int i = 0; i <= m; i++) {
        lookup[i][0] = i;
    }
 
    // initialize the first row of the lookup table
    for (int j = 0; j <= n; j++) {
        lookup[0][j] = j;
    }
 
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
            else {
                lookup[i][j] = std::min(lookup[i - 1][j] + 1, lookup[i][j - 1] + 1);
            }
        }
    }


    return lookup[m][n];
    
}