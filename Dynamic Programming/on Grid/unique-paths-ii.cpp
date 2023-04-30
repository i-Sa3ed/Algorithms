#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset

using namespace std;

/// https://leetcode.com/problems/unique-paths-ii/

const int MAX = 100;
int memory[MAX][MAX];

class Solution {
    vector<vector<int>> obstacleGrid;
    int n, m;
public:
    bool out_of_bounds(int i, int j) {
        return (i >= n) or (j >= m);
    }
    int dp_count_paths(int i = 0, int j = 0) {
        if (out_of_bounds(i, j) or obstacleGrid[i][j] == 1)
            return 0;
        else if (i == n-1 and j == m-1)
            return 1; // one valid path

        auto& ret = memory[i][j];
        if (ret != -1)
            return ret;

        // next steps
        int bottom = dp_count_paths(i + 1, j),
            right = dp_count_paths(i, j + 1);
        return ret = bottom + right;
    }
    int uniquePathsWithObstacles(vector<vector<int>>& _obstacleGrid) {
        memset(memory, -1, sizeof(memory));
        obstacleGrid = _obstacleGrid;
        n = obstacleGrid.size(), m = obstacleGrid[0].size();

        return dp_count_paths();
    }
};

int main() {

    return 0;
}