
#include <string>
#include <vector>
#include <iostream>


/**
 * Given a list X, returns the longest subsequence such that elements of X are from lowest to highest order (ascending)
 * 
 * Note: U is subsequence of V iff U is contained in V non-consecutively
 */


// Note that elements of list should be comparable
void findLIS(std::vector<int> const &arr)
{
    int n = arr.size();
 
    // base case
    if (n == 0) {
        return;
    }
 
    std::vector<std::vector<int>> LIS(n, std::vector<int>{});
 
    LIS[0].push_back(arr[0]);
 
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
 
            if (arr[j] < arr[i] && LIS[j].size() > LIS[i].size()) {
                LIS[i] = LIS[j];
            }
        }
 
        LIS[i].push_back(arr[i]);
    }
  
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (LIS[j].size() < LIS[i].size()) {
            j = i;
        }
    }
 
    // print LIS
    for (int i: LIS[j]) {
        std::cout << i << " ";
    }
}