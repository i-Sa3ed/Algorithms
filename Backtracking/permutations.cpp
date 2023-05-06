#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset
#include <map>

using namespace std;

/// https://leetcode.com/problems/permutations/

class Solution {
    int n;
    vector<int> nums,
        permutation; // common state
    vector< vector<int> > result;
    map<int, bool> reserved;

public:
    void backtrack() {
        if (permutation.size() == n) {
            result.push_back(permutation);
            return;
        }

        for (int num : nums) {
            if (reserved[num])
                continue;

            permutation.push_back(num); // add
            reserved[num] = true; // mark

            backtrack();

            reserved[num] = false; // un-mark
            permutation.pop_back(); // undo
        }
    }
    vector<vector<int>> permute(vector<int>& _nums) {
        nums = _nums;
        n = nums.size();

        backtrack();

        return result;
    }
};

int main() {

    return 0;
}