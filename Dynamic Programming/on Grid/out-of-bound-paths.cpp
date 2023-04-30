#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset

using namespace std;

/// https://leetcode.com/problems/out-of-boundary-paths/

int dr4[4] = {-1, 1, 0, 0}; // delta for: up, down, left, right
int dc4[4] = {0, 0, -1, 1};

const int MAX = 50 + 1, mod = 1e9 + 7;
long long memory[MAX][MAX][MAX];

class Solution {
    int n, m;

public:
    bool out_of_bounds(int i, int j) {
        return (i < 0 or i >= n) or (j < 0 or j >= m);
    }

    long long dp_count_paths(int i, int j, int maxMoves) {
        if (out_of_bounds(i, j))
            return 1; // +1 valid path

        auto& ret = memory[i][j][maxMoves];
        if (ret != -1)
            return ret;

        if (maxMoves == 0)
            return 0; // no more possible moves

        // next moves
        ret = 0;
        for (int d = 0; d < 4; ++d) {
            ret += dp_count_paths(i + dr4[d], j + dc4[d], maxMoves - 1);
            ret %= mod;
        }

        return ret;
    }
    long long findPaths(int _m, int _n, int maxMove, int startRow, int startColumn) {
        n = _m; // use n for rows and m for cols
        m = _n;

        memset(memory, -1, sizeof(memory));

        // we don't need to worry about cycles, because 'maxMoves' will force our recursion to stop.
        return dp_count_paths(startRow, startColumn, maxMove);
    }
};

int main() {
    Solution solution;
    cout << solution.findPaths(2, 2, 2, 0, 0);

    return 0;
}