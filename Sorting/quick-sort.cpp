/// https://leetcode.com/problems/sort-an-array/
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

/* // some quick sort properties:
 * in-place algo
 * has worst case = N^2
 * average = N logN
 */

class Solution {
    int PARTITION(vector<int>& vec, int l, int h, int pivot) {
        int cur = l - 1;
        for (int i = l; i < h; ++i) {
            if (vec[i] <= vec[pivot]) {
                ++cur;
                swap(vec[i], vec[cur]);
            }
        }

        ++cur;
        swap(vec[pivot], vec[cur]);
        return cur;
    }
public:
    void quick_sort(vector<int>& vec, int l, int h) {
        /// handle the worst case
        // test if sorted
        if (l == 0 and h == vec.size() - 1) {
            vector<int> rev = vec;
            reverse(rev.begin(), rev.end());
            if (is_sorted(vec.begin(), vec.end()))
                return;
            if (std::is_sorted(rev.begin(), rev.end())) {
                vec = rev;
                return;
            }
        }
        // one of the ideas is to shuffle the partition randomly
        shuffle(vec.begin() + l, vec.begin() + (h + 1), std::mt19937{std::random_device{}()});

        if (l < h) {
            // there are many ways to choose the pivot
            // let's try the last item
            int pivot = h;

            int idx = PARTITION(vec, l, h, pivot);

            quick_sort(vec, l, idx - 1);
            quick_sort(vec, idx + 1, h);
        }
    }
    vector<int> sortArray(vector<int>& nums) {
        quick_sort(nums, 0, nums.size()-1);
        return nums;
    }
};

int main() {
    vector<int> vec = {5,1,1,2,0,0};
    Solution solution;
    solution.sortArray(vec);


    return 0;
}