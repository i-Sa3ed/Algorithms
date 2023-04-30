#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset

using namespace std;

/// https://leetcode.com/problems/coin-change-ii/

const int MAX = 5000 + 1;
int memory[MAX];
class Solution {
    vector<int> coins;
public:
    int dp_count(int rem_amount) {
        if (rem_amount == 0)
            return 1; // one valid path

        auto& ret = memory[rem_amount];
        if (ret != -1)
            return ret;

        ret = 0;
        for (int c : coins)
            if (c <= rem_amount)
                ret += dp_count(rem_amount - c); // pick it

        return ret;
    }
    int change(int amount, vector<int>& _coins) {
        coins = _coins;
        sort(coins.begin(), coins.end());
        memset(memory, -1, sizeof(memory));
        return dp_count(amount);
    }
};

int main() {
    Solution solution;
    int amount; cin >> amount;
    vector<int> coins = {1, 2, 5};
    cout << solution.change(amount, coins);

    return 0;
}