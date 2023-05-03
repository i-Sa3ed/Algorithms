#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset
#include <cassert>

using namespace std;

/// recall coin-change problem, from Counting section
/// https://leetcode.com/problems/coin-change-ii/
// let's try to solve it using Tabulation

const int MAX_AMOUNT = 5000 + 1, MAX_IDX = 300;
int memory[MAX_IDX][MAX_AMOUNT];
class Solution {
public:
    // helper function, saves the time and thinking :)
    int answer(int idx, int target) {
        if (target < 0) return 0;
        if (target == 0) return 1; // +1 valid path
        if (idx < 0) return 0; // no more coins to pick :(

        assert(memory[idx][target] != -1); /// for safety
        return memory[idx][target];
    }
    int change(int amount, vector<int>& coins) {
        memset(memory, -1, sizeof(memory));
        int n = coins.size();

        // major loop: over the index
        for (int idx = 0; idx < n; ++idx) {
            // try all possible amounts, from smaller to larger
            for (int target = 0; target <= amount; ++target) {
                int pick = answer(idx, target - coins[idx]),
                    leave = answer(idx - 1, target);
                memory[idx][target] = pick + leave;
            }
        }

        return memory[n-1][amount];
    }

    /// Notice that: using Tabulation, we can reduce the memory
    // to memory[2][M]
    // because we only need the last 2 indices

    // and even more to just memory[M] !!
    int change(int amount, vector<int>& coins, bool linear_memory = true) {
        // non-reachable cases => 0 count
        int memory1D[MAX_AMOUNT];
        memset(memory1D, 0, sizeof(memory1D));

        // base case:
        memory1D[0] = 1; // if target = 0, we can just leave all coins and get it ;)

        for (int idx = 0; idx < coins.size(); ++idx) {
            for (int target = coins[idx]; target <= amount; ++target) {
                memory1D[target] += memory1D[target - coins[idx]];
            }
        }

        return memory1D[amount];
    }
};



int main() {

    return 0;
}