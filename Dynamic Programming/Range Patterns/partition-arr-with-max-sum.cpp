#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset

using namespace std;

/// https://leetcode.com/problems/partition-array-for-maximum-sum/
const int MAX = 500;
int memory[MAX];

class Solution {
    vector<int> array;
    int n, mxPartSize;
public:
    int dp_max_sum(int idx = 0) {
        if (idx == n)
            return 0;

        auto& ret = memory[idx];
        if (ret != -1)
            return ret;

        // next
        int cnt = 0, mxVal = 0;
        for (int endIdx = idx; endIdx < n; ++endIdx) {
            ++cnt;
            if (cnt > mxPartSize)
                break;

            mxVal = max(mxVal, array[endIdx]);
            ret = max(ret, cnt*mxVal + dp_max_sum(endIdx + 1));
        }

        return ret;
    }
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        memset(memory, -1, sizeof(memory));
        array = arr;
        n = arr.size();
        mxPartSize = k;

        return dp_max_sum();
    }
};

int main() {

    return 0;
}