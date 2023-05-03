#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset

using namespace std;

/// https://leetcode.com/problems/number-of-dice-rolls-with-target-sum/
// let's solve it again using Tabulation

const int MAX_N = 30 + 1, MAX_T = 1000 + 1;
long long memory[MAX_N][MAX_T];
const int mod = 1e9 + 7;

class Solution {
public:
    int numRollsToTarget(int n, int k, int target) {
        memset(memory, 0, sizeof(memory));
        // base case
        memory[0][0] = 1;

        // major loop (over dices)
        for (int dice = 1; dice <= n; ++dice) {
            for (int tar = 1; tar <= target; ++tar) {
                long long& count = memory[dice][tar];
                for (int face = 1; face <= min(tar, k); ++face) {
                    count += memory[dice-1][tar - face];
                    count %= mod;
                }
            }
        }

        return memory[n][target];
    }
};

int main() {

    return 0;
}