/// https://leetcode.com/problems/sort-an-array/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset
#include <map>
#include <random>

using namespace std;

/// TLE !
class Solution {
public:
    int partition(vector<int>& arr, int start, int end) {
        // let's choose the pivot in the middle
        int mid = start + (end - start) / 2;
        int pivot = arr[mid];

        int pivot_idx = start;
        for (int i = start; i <= end; ++i)
            if (arr[i] <= pivot and i != mid)
                ++pivot_idx;
        swap(arr[pivot_idx], arr[mid]); // put the mid in its right location

        // swap each item to its correct half
        for (int s = start, e = end; s < pivot_idx and e > pivot_idx; ++s, --e) {
            // find the first item > pivot; and located before it
            while (arr[s] <= pivot)
                ++s;

            // find the last item <= pivot; and located after it
            while (arr[e] > pivot)
                --e;

            if (s < pivot_idx and e > pivot_idx)
                swap(arr[s], arr[e]);
        }

        return pivot_idx;
    }

    void quick_sort(vector<int>& arr, int start, int end) {
        if (start >= end)
            return;

        // randomly shuffle the partition => to avoid worst case
        //shuffle(arr.begin() + start, arr.begin() + (end + 1), std::mt19937{std::random_device{}()});

        int pivot = partition(arr, start, end);
        quick_sort(arr, start, pivot - 1);
        quick_sort(arr, pivot + 1, end);
    }

    vector<int> sortArray(vector<int>& nums) {
        vector<int> sorted = nums;
        quick_sort(sorted, 0, sorted.size() - 1);
        return sorted;
    }
};


int main() {
    vector<int> v = {-4,0,7,4,9,-5,-1,0,-7,-1};
    Solution solution;
    v = solution.sortArray(v);


    return 0;
}