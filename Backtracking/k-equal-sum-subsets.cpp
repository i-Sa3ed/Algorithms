#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset
#include <numeric> // accumulate

using namespace std;

/// https://leetcode.com/problems/partition-to-k-equal-sum-subsets/

/// First perspective: Number searches for the partition
class Solution_1 {
    int k;
    vector<int> nums;

    int partitionSize;
    vector<int> partitions_cur_state;
    bool possible = false;

public:
    void try_partition(int idx = 0) { // O(k^n) [n = nums.size]
        if (possible) // we reached our goal already
            return;

        if (idx == nums.size()) {
            // if all numbers are added => we have a solution
            // BUT, why you are sure?!
                // because we have a limit for each partition, which force them to be balanced ;)

            possible = true;
            return;
        }

        for (int part = 0; part < k; ++part) {
            if (nums[idx] + partitions_cur_state[part] <= partitionSize) {
                partitions_cur_state[part] += nums[idx]; // add it
                try_partition(idx + 1);
                partitions_cur_state[part] -= nums[idx]; // undo
            }
        }
    }
    bool canPartitionKSubsets(vector<int>& _nums, int _k) {
        nums = _nums;
        k = _k;

        int acc = accumulate(nums.begin(), nums.end(), 0);
        if (acc % k != 0)
            return false;

        partitionSize = acc / k;
        partitions_cur_state = vector<int>(k);

        try_partition();

        return possible;
    }
};

/// Second perspective: Partition searches for its numbers
class Solution {
    int k;
    vector<int> nums;

    int partitionSize;
    vector<bool> selected; // shared state

public:
    bool try_partition(int partitionIdx = 0, int numIdx = 0, int cur_sum = 0) { // O(k * 2^n)
        if (partitionIdx == k) // finished all partitions successfully
            return true;
        if (cur_sum == partitionSize)
            return try_partition(partitionIdx + 1, 0, 0);
        if (cur_sum > partitionSize or numIdx == nums.size())
            return false;

        // do the normal Pick or leave, O(2^n)
        bool pick = false;
        if (!selected[numIdx]) {
            selected[numIdx] = true; // update the state
            pick = try_partition(partitionIdx, numIdx + 1, cur_sum + nums[numIdx]);
            selected[numIdx] = false; // undo
        }
        if (pick) // stop as early as possible
            return true;

        bool leave = try_partition(partitionIdx, numIdx + 1, cur_sum);
        if (leave)
            return true;

        return false; // neither pick nor leave are valid!
    }
    bool canPartitionKSubsets(vector<int>& _nums, int _k) {
        nums = _nums;
        k = _k;

        int acc = accumulate(nums.begin(), nums.end(), 0);
        if (acc % k != 0)
            return false;

        partitionSize = acc / k;
        selected = vector<bool> (nums.size());

        return try_partition();
    }
};


int main() {
    Solution solution;
    vector<int> nums = {2,2,2,2,3,4,5};
    int k = 4;
    cout << solution.canPartitionKSubsets(nums, k);

    return 0;
}