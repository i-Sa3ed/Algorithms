/// https://leetcode.com/problems/global-and-local-inversions/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset
#include <map>

using namespace std;

// it's the merge sort code, with a minor change

class Solution {
    int n;
    vector<int> nums, original;
    vector<int> temp;

    long long global_inv = 0;

public:
    void MERGE(int start, int mid, int end) {
        // merge 2 sorted sub-arrays

        for (int i1 = start, i2 = mid+1, k = start; k <= end; ++k) {
            // k => index of temp
            // i1, i2 => indices of 2 sub-arrays to be merged

            /// we increase 'inv' when we pick from the first sub-array (let's call it x)
            // you can say: "how many items added from the second sub before the x comes?"
            // the answer is the inversions of x.

            if (i1 > mid) // first sub-array finished?
                temp[k] = nums[i2++];
            else if (i2 > end) // second sub-array finished?
                temp[k] = nums[i1++], global_inv += (i2 - (mid + 1));
            else if (nums[i1] <= nums[i2])
                temp[k] = nums[i1++], global_inv += (i2 - (mid + 1));
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

    int count_local_inv() {
        int local_inv = 0;
        for (int i = 0; i < n - 1; ++i) {
            if (original[i] > original[i+1])
                ++local_inv;
        }

        return local_inv;
    }
    bool isIdealPermutation(vector<int>& _nums) {
        original = nums = _nums;
        n = nums.size();
        temp = nums;

        merge_sort(0, n-1); // this counts global inv
        int local_inv = count_local_inv();
        return (global_inv == local_inv);
    }
};

int main() {

    return 0;
}