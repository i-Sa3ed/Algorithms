#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset

using namespace std;

/// https://leetcode.com/problems/min-cost-climbing-stairs/

const int MAX = 1005;
int memory[MAX];
class Solution {
    int n;
    vector<int> costs;
public:
    int dp_min(int idx) {
        if (idx >= n)
            return 0;

        auto& ret = memory[idx];
        if (ret != -1)
            return ret;

        // next choices:
        int jumpOne = dp_min(idx + 1),
            jumpTwo = dp_min(idx + 2);
        ret = costs[idx] + min(jumpOne, jumpTwo);

        return ret;
    }
    int minCostClimbingStairs(vector<int>& cost) {
        n = cost.size();
        costs = cost;
        memset(memory, -1, sizeof(memory));
        return min(dp_min(0), dp_min(1));
    }
};

int main() {

    return 0;
}