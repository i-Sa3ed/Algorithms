#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset

using namespace std;

/// https://leetcode.com/problems/combination-sum-iv/

const int MAX = 1000 + 1;
int memory[MAX];
class Solution {
    vector<int> nums;
    int n;
public:
    int dp_count(int target) {
        if (target == 0)
            return 1; // one valid path

        auto& ret = memory[target];
        if (ret != -1)
            return ret;

        ret = 0;
        for (int i = 0; i < n and nums[i] <= target; ++i) {
            ret += dp_count(target - nums[i]);
        }

        return ret;
    }
    int combinationSum4(vector<int>& _nums, int target) {
        nums = _nums;
        n = nums.size();
        sort(nums.begin(), nums.end());
        memset(memory, -1, sizeof(memory));
        return dp_count(target);
    }
};

int main() {

    return 0;
}