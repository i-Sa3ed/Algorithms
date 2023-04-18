// longest increasing subsequence problem with DP

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

/// https://leetcode.com/problems/longest-increasing-subsequence/

int n;
vector<int> seq;
vector< vector<int> > memory2; // 2d memory

int lis(int idx, int lastIdx) {
    /*
     * time: O(n^2)
     * memory2: same
     */
    if (idx >= n)
        return 0;


    // memoization:
    auto &ref = memory2[idx][lastIdx];
    if (ref != -1) // stored before
        return ref;

    // pick if possible:
    int pick_choice = 0;
    if (lastIdx == n /* first call */ or seq[idx] > seq[lastIdx])
        pick_choice = 1 + lis(idx+1, idx); // next last = cur

    // leave:
    int leave_choice = lis(idx+1, lastIdx);

    return ref = max(pick_choice, leave_choice);
}

/// another implementation
// definition: lis(idx) = idx is a part of the sequence (force pick)
/// https://leetcode.com/problems/longest-increasing-subsequence/

vector<int> memory1; // 1d memory
int lis(int idx, vector<int>& arr) {
    /*
     * time: O(n^2)
     * memory: O(n)
     */

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

    // Notice: this implementation is more "stack-friendly"
    // because we make calls only for next VALID positions
}
int solve_lis(vector<int>& arr) {
    // trick:
    // instead of looping: we can add a small value and use it as a starting point ;)
    arr.insert(arr.begin(), INT_MIN);

    n = arr.size();
    memory1 = vector<int>(n, -1);

    /*for (int i = 0; i < n; ++i) {
        ans = max(ans, lis(i, arr));
    }*/

    int ans = lis(0, arr) - 1; // -1 = remove the added item.
    return ans;
}

int main() {
    cin >> n;
    memory2 = vector< vector<int> >(n + 1, vector<int>(n + 1, -1));
    //seq = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
    seq.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> seq[i];
    }

    cout << solve_lis(seq) << endl;

    return 0;
}