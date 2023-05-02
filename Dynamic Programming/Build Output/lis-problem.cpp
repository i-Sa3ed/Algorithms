#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset

using namespace std;

int n;
vector<int> memory1; // 1d memory

int lis(int idx, vector<int>& arr) {
    if (idx >= n)
        return 0;

    // memoization
    auto& ret = memory1[idx];
    if (ret != -1)
        return ret;

    ret = 0;
    // next choices:
    for (int i = idx+1; i < n; ++i) {
        if (arr[i] > arr[idx]) // possible
            ret = max(ret, lis(i, arr)); // solve the subproblem
    }

    ret += 1; // for current idx
    return ret;
}

void dp_print(int idx, vector<int>& nums, vector<int>& path) {
    if (idx == n)
        return;

    if (idx) // don't add the dummy value
        path.push_back(nums[idx]);

    int optimal = lis(idx, nums);

    // choose the next choice:
    for (int i = idx + 1; i < n; ++i) {
        if (nums[i] > nums[idx]) {
            int choice = 1 + lis(i, nums);
            if (choice == optimal) { // found an optimal sub-path
                dp_print(i, nums, path);
                return;
            }
        }
    }
}

vector<int> LIS(vector<int>& nums) {
    nums.insert(nums.begin(), INT_MIN); // as a starting point
    n = nums.size();
    memory1 = vector<int>(n, -1);

    vector<int> output;
    dp_print(0, nums,output);

    return output;
}

int main() {
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    vector<int> lis = LIS(nums);

    return 0;
}