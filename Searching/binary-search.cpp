#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/// https://leetcode.com/problems/binary-search/
int search(vector<int>& nums, int target) {
    int res = -1;
    int l = 0, r = nums.size() - 1;
    while (l <= r) {
        int m = l + (r - l) / 2; // to avoid overflow
        if (nums[m] == target) {
            res = m;
            break;
        } else if (target > nums[m]) // search on the right side
            l = m + 1;
        else // search on the left side
            r = m - 1;
    }

    return res;
}


/// equal range:
// returns both lower and upper bounds for a value

/// https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
// using my own binary search function
int find_first(vector<int>& nums, int val) {
    int res = -1;
    int start = 0, end = nums.size() - 1;
    while (start <= end) {
        int m = start + (end - start) / 2;
        if (nums[m] == val) {
            res = m;
            end = m - 1; // minimize as you can
        }
        else if (val > nums[m])
            start = m + 1;
        else
            end = m - 1;
    }

    return res;
}
int find_last(vector<int>& nums, int val) {
    int res = -1;
    int start = 0, end = nums.size() - 1;
    while (start <= end) {
        int m = start + (end - start) / 2;
        if (nums[m] == val) {
            res = m;
            start = m + 1; // maximize as you can
        }
        else if (val > nums[m])
            start = m + 1;
        else
            end = m - 1;
    }

    return res;
}
vector<int> searchRange_(vector<int>& nums, int target) {
    vector<int> res(2);
    res[0] = find_first(nums, target);
    res[1] = find_last(nums, target);

    return res;
}

// using "equal range" function
vector<int> searchRange(vector<int>& nums, int target) {
    vector<int> res = {-1, -1};

    // use equal_range function
    auto range = equal_range(nums.begin(), nums.end(), target);
    if (range.first != range.second) // exist
        res[0] = range.first - nums.begin(), res[1] = range.second - nums.begin() - 1;

    return res;
}

////////////////////////////////////////////////////

void test() {
    vector<int> nums = {1, 1, 3, 4, 4, 7};
    vector<int> res = searchRange_(nums, 3);
    cout << res[0] << ' ' << res[1] << endl;
}

int main()
{
    test();

    return 0;
}