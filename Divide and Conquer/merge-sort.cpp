/// https://leetcode.com/problems/sort-an-array/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset
#include <map>

using namespace std;

class Solution {
    int n;
    vector<int> nums;
    vector<int> temp;
public:
    void MERGE(int start, int mid, int end) {
        // merge 2 sorted sub-arrays

        for (int i1 = start, i2 = mid+1, k = start; k <= end; ++k) {
            // k => index of temp
            // i1, i2 => indices of 2 sub-arrays to be merged

            if (i1 > mid) // first sub-array finished?
                temp[k] = nums[i2++];
            else if (i2 > end) // second sub-array finished?
                temp[k] = nums[i1++];
            else if (nums[i1] <= nums[i2])
                temp[k] = nums[i1++];
            else
                temp[k] = nums[i2++];
        }

        // copy from 'temp' to original
        for (int k = start; k <= end; ++k)
            nums[k] = temp[k];
    }
    void merge_sort(int start, int end) {
        if (start >= end)
            return;

        int mid = start + (end - start)/2;
        merge_sort(start, mid);
        merge_sort(mid + 1, end);
        MERGE(start, mid, end);

    }
    vector<int> sortArray(vector<int>& _nums) {
        nums = _nums;
        n = nums.size();
        temp = nums;

        merge_sort(0, n-1);
        return nums;
    }
};


int main() {
    vector<int> nums = {5,2,3,1};
    Solution solution;
    nums = solution.sortArray(nums);

    return 0;
}