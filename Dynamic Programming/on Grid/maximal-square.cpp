#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset

using namespace std;

/// https://leetcode.com/problems/maximal-square/

const int MAX = 300;
int memory[MAX][MAX];

class Solution {
    vector<vector<char>> matrix;
    int n, m;
public:
    int dp_max_area(int i, int j) { // returns the max 1s area starting from (i, j)
        if ((i >= n or j >= m) or matrix[i][j] == '0')
            return 0;

        auto& ret = memory[i][j];
        if (ret != -1)
            return ret;

        // next moves
        int right = dp_max_area(i, j + 1),
            bottom = dp_max_area(i + 1, j),
            diagonal = dp_max_area(i + 1, j + 1);
        ret = 1 + min({right, bottom, diagonal}); // current cell + min of my children

        return ret;
    }
    int maximalSquare(vector<vector<char>> _matrix) {
        matrix = _matrix;
        n = matrix.size(), m = matrix[0].size();

        memset(memory, -1, sizeof(memory));

        int maxDimension = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (matrix[i][j] == '1')
                    maxDimension = max(maxDimension, dp_max_area(i, j));
            }
        }
        return maxDimension * maxDimension;
    }
};

int main() {
    Solution solution;
    vector< vector<char> > matrix1 = {{'1', '0', '1', '0', '0' }, {'1', '0', '1', '1', '1' }, {'1', '1', '1', '1', '1' }, {'1', '0', '0', '1', '0' }};
    vector< vector<char> > matrix2 = { {'1', '1', '1'}, {'1', '1', '1'}, {'1', '1', '1'} };
    cout << solution.maximalSquare(matrix2);

    return 0;
}