#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset

using namespace std;

/// https://leetcode.com/problems/minimum-falling-path-sum/

class Solution {
    vector<vector<int>> matrix;
    vector< vector<int> > memory;
    int n;

public:
    int dp_min_path(int i, int j) {
        if (i >= n or j >= n or j < 0)
            return 1e9; // out of bounds? => avoid it
        else if (i == n-1)
            return matrix[i][j]; // reached the goal

        auto& ret = memory[i][j];
        if (ret != -1e5)
            return ret;

        ret = matrix[i][j];
        // next moves
        int below = dp_min_path(i + 1, j),
            diag_left = dp_min_path(i + 1, j - 1),
            diag_right = dp_min_path(i + 1, j + 1);
        ret += min({below, diag_left, diag_right});

        return ret;
    }
    int minFallingPathSum(vector<vector<int>>& _matrix) {
        matrix = _matrix;
        n = matrix.size();
        // notice that initializing memory with -1 is not efficient here, because it's a possible value.
        memory = vector< vector<int> >(n, vector<int>(n, -1e5));

        int ans = INT_MAX;
        for (int j = 0; j < n; ++j) {
            ans = min(ans, dp_min_path(0, j));
        }
        return ans;
    }
};

int main() {
    Solution solution;
    vector< vector<int> > matrix = {{1, 2}, {4, 3}};
    cout << solution.minFallingPathSum(matrix);

    return 0;
}