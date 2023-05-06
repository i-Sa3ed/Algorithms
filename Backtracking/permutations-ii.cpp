/// https://leetcode.com/problems/permutations-ii/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset
#include <map>

using namespace std;

/*
 * we have duplicates, how to handle them?
 * we should work on the unique set..
 *
 * But, how to obtain and handle it?
 * Simply by using a map.
 */
class Solution {
    int n;
    vector<int> permutation; // common state
    vector< vector<int> > result;
    map<int, int> frq;

public:
    void backtrack() {
        if (permutation.size() == n) {
            result.push_back(permutation);
            return;
        }

        for (auto& [num, f] : frq) {
            if (f == 0)
                continue;

            permutation.push_back(num); // add
            f--;

            backtrack();

            f++;
            permutation.pop_back(); // undo
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        n = nums.size();
        for (int& num : nums)
            frq[num]++;

        backtrack();
        return result;
    }
};

int main() {

    return 0;
}