#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset

using namespace std;

/// recall: the LIS problem
/// https://leetcode.com/problems/longest-increasing-subsequence/
// we will now use the "Tabulation" to solve it, rather than the "Memoization"

const int MAX = 2500 + 5;
int memory[MAX];

class Solution {
    int n;

public:
    int lengthOfLIS(vector<int>& nums) {
        /// we will go in the reverse order
        // from 0 to n - 1

        // to ensure that `memory[n-1]` is included in my solution
        nums.insert(nums.end(), INT_MAX);
        n = nums.size();

        // base case
        memory[0] = 1;

        for (int i = 1; i < n; ++i) {
            // Notice: the same memoization code!

            auto& ret = memory[i];
            // Now, let's go and build it:
            ret = 1;
            for (int j = i - 1; j >= 0; --j)
                if (nums[j] < nums[i])
                    ret = max(ret, 1 + memory[j]);
        }

        return memory[n-1] - 1; // -1 => to remove the added element
    }
};

int main() {
    Solution solution;
    vector<int> nums = {0,1,0,3,2,3};
    cout << solution.lengthOfLIS(nums);

    return 0;
}