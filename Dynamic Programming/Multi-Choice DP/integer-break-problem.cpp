#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

/// https://leetcode.com/problems/integer-break/

const int MAX = 60;
int memory[MAX];
class Solution {
    int nn;
public:
    int dp_max(int rem) {
        if (rem <= 1)
            return 1;

        auto& ret = memory[rem];
        if (ret != -1)
            return ret;

        // next choices:
        int choice = 0;
        for (int next = 1; next <= rem; ++next) {
            if (rem == nn and next == rem) // first call
                break; // to avoid case of k = 1

            int pick = next * dp_max(rem - next);
            choice = max(choice, pick);
        }

        return ret = choice;
    }
    int integerBreak(int n) {
        nn = n;
        memset(memory, -1, sizeof(memory));
        return dp_max(n);
    }
};

int main() {
    Solution sol;
    cout << sol.integerBreak(10);

    return 0;
}