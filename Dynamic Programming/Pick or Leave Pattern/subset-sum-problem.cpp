#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/// https://practice.geeksforgeeks.org/problems/subset-sum-problem-1611555638/1

// which to prioritize?
    // fast memset init, or
    // customized vector memory
vector< vector<int> > memory;
int n;
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
bool subset_sum(vector<int>& values, int target) {
    n = values.size();
    memory = vector< vector<int> >(n, vector<int>(target+5, -1));

    return has_sum(values, target);
}

int main() {
    int siz; cin >> siz;
    vector<int> values(siz);
    for (int i = 0; i < siz; ++i) {
        cin >> values[i];
    }
    int sum; cin >> sum;

    cout << subset_sum(values, sum) << endl;

    return 0;
}