#include <string>
#include <vector>
#include <algorithm>

#include <iostream>







/**
 * Minimum distance between two words is the minimum number of single-character changes (i.e., insertions, deletions, or substitutions) 
 * required to transform one word into the other. Each of these operations has a unit cost.
 */

int dist(std::string X, std::string Y)
{
    int m = X.length();
    int n = Y.length();
 
    std::vector<std::vector<int>> T (m+1, std::vector<int>(n+1, 0) );

 
    // we can transform source prefixes into an empty string by
    // dropping all characters
 
    for (int i = 1; i <= m; i++) {
        T[i][0] = i;                // (case 1)
    }
 
    // we can reach target prefixes from empty source prefix
    // by inserting every character
 
    for (int j = 1; j <= n; j++) {
        T[0][j] = j;                // (case 1)
    }
 
    int substitutionCost;
 
    // fill the lookup table in a bottom-up manner
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (X[i - 1] == Y[j - 1]) {                 // (case 2)
                substitutionCost = 0;                   // (case 2)
            }
            else {
                substitutionCost = 1;                   // (case 3c)
            }
            T[i][j] = std::min(std::min(T[i - 1][j] + 1,          // deletion (case 3b)
                            T[i][j - 1] + 1),           // insertion (case 3a)
                T[i - 1][j - 1] + substitutionCost);    // replace (case 2 & 3c)
        }
    }
 
    return T[m][n];
}