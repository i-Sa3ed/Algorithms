#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset

using namespace std;

/// https://leetcode.com/problems/number-of-dice-rolls-with-target-sum/

const int MAX_N = 30 + 1, MAX_T = 1000 + 1;
long long memory[MAX_N][MAX_T];
const int mod = 1e9 + 7;

class Solution {
    int k;
public:
    long long dp_count(int n, int target) {
        if (n == 0) {
            if (target == 0)
                return 1; // one valid path
            else
                return 0;
        }
        if (target <= 0)
            return 0;

        // target by itself is NOT enough to represent the state
        auto& ret = memory[n][target];
        if (ret != -1)
            return ret;

        ret = 0;
        for (int face = 1; face <= k; ++face) {
            ret += dp_count(n-1, target - face);
            ret %= mod;
        }

        return ret;
    }
    int numRollsToTarget(int n, int _k, int target) {
        k = _k;
        memset(memory, -1, sizeof(memory));
        return dp_count(n, target);
    }
};

int main() {
    Solution solution;
    cout << solution.numRollsToTarget(30, 30, 500) << endl;

    return 0;
}