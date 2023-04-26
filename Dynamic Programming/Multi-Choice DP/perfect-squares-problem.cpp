#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset

using namespace std;

/// https://leetcode.com/problems/perfect-squares/

const int MAX = 1e4 + 5;
int memory[MAX];
class Solution {
    vector<int> perfectSquares;
public:
    void generate_PSs() {
        for (int i = 1; i*i <= MAX; ++i)
            perfectSquares.push_back(i*i);
    }
    int dp_min(int n) {
        if (n == 0)
            return 0;

        auto& ret = memory[n];
        if (ret != -1)
            return ret;

        // next choices: all PSs that are <= n
        int choice = INT_MAX;
        for (int ps : perfectSquares) {
            if (ps > n)
                break;
            choice = min(choice, 1 + dp_min(n - ps));
        }

        return ret = choice;
    }
    int numSquares(int n) {
        memset(memory, -1, sizeof(memory));
        generate_PSs();
        int siz = perfectSquares.size();
        return dp_min(n);
    }
};

int main() {
    Solution sol;
    cout << sol.numSquares(12) << endl;

    return 0;
}