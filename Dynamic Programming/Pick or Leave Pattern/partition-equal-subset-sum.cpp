#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cstring>

using namespace std;

/// https://leetcode.com/problems/partition-equal-subset-sum/

const int MAX_N = 200, MAX_T = 20000 + 1;
class Solution {
    int n;
    int memory[MAX_N][MAX_T];
    int accumulate(vector<int>& nums) {
        int res = 0;
        for(int i : nums)
            res += i;
        return res;
    }
public:
    bool has_sum(vector<int>& values, int target, int idx = 0, int sum = 0) {
        /*
         * time: O(NT) [N = values.size, T = target]
         * memory: same
         */
        // cancel invalid states:
        if (target < 0)
            return false;
        if (target == 0)
            return true;
        if (sum == target)
            return true;
        if (idx >= n)
            return false;

        auto& ret = memory[idx][sum];
        if (ret != -1)
            return ret;

        bool pick = (sum + values[idx] <= target) and
                    has_sum(values, target, idx+1, sum + values[idx]);
        bool leave = has_sum(values, target, idx+1, sum);

        return ret = (pick or leave);
    }

    bool canPartition(vector<int>& nums) {
        n = nums.size();
        memset(memory, -1, sizeof(memory));

        int sum = accumulate(nums);
        if (sum%2 == 1) // sum can't be divided into 2 int parts.
            return false;

        // if the arr has subset of sum/2, then it implies that there is another equal subset.
        return has_sum(nums, sum/2);
    }
};

int main() {

    return 0;
}