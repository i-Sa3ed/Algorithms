#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset
#include <cassert>

using namespace std;

/// https://leetcode.com/problems/out-of-boundary-paths/
// let's solve it with Tabulation

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

    // helper function
    int answer(int i, int j, int moves) {
        if (out_of_bounds(i, j))
            return 1;
        return memory[i][j][moves];
    }

    long long findPaths(int _m, int _n, int maxMove, int startRow, int startColumn) {
        n = _m; // use n for rows and m for cols
        m = _n;

        memset(memory, 0, sizeof(memory));

        for (int moves = 1; moves <= maxMove; ++moves) { // the actual indexing, so it comes first
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    long long &count = memory[i][j][moves];
                    for (int d = 0; d < 4; ++d) {
                        count += answer(i + dr4[d], j + dc4[d], moves - 1);
                        count %= mod;
                    }
                }
            }
        }

        return memory[startRow][startColumn][maxMove];
    }
};

int main() {

    return 0;
}