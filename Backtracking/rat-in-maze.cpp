#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset

using namespace std;

/// https://practice.geeksforgeeks.org/problems/rat-in-a-maze-problem/1?utm_source=geeksforgeeks&utm_medium=article_practice_tab&utm_campaign=article_practice_tab
// why can't be solved with DP?
// because we need to mark a 2d visited array, which is huge and doesn't fit in the memory!

class Solution{
    int n;
    vector<vector<int>> maze;
    vector<string> result;

    int dr[4] = {-1, 1, 0, 0}; // delta for: up, down, left, right
    int dc[4] = {0, 0, -1, 1};
    char dir[4] = {'U', 'D', 'L', 'R'};

public:
    bool out_of_bounds(int i, int j) {
        return (i < 0 or i >= n) or (j < 0 or j >= n);
    }
    void backtrack(int i = 0, int j = 0, string path = "") {
        if (out_of_bounds(i, j) or maze[i][j] == 0)
            return;
        if (i == n-1 and j == n-1) { // reach the goal
            result.push_back(path);
            return;
        }

        // update
        maze[i][j] = 0; // visited

        // try 4 directions:
        for (int d = 0; d < 4; ++d) {
            string next_path = path + dir[d];
            backtrack(i + dr[d], j + dc[d], next_path);
        }

        // undo
        maze[i][j] = 1;
    }
    vector<string> findPath(vector<vector<int>> &m, int _n) {
        n = _n;
        maze = m;

        backtrack();
        sort(result.begin(), result.end());
        return result;
    }
};


int main() {

    return 0;
}