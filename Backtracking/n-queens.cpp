#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset

using namespace std;

/// https://leetcode.com/problems/n-queens/

class Solution {
    int n;
    vector< vector<string> > boards;
    vector<string> board; // shared state
public:
    bool valid(int row, int col) {
        return (row >= 0 and row < n) and (col >= 0 and col < n);
    }
    bool free_of_attacks(int r, int c) {
        // row is guaranteed to be valid

        // test column
        for (int i = 0; i < n; ++i) {
            if (board[i][c] == 'Q')
                return false;
        }

        /// test diagonals:
        for (int d = 1; d < n; ++d) {
            // main diagonal
            if ((valid(r + d, c + d) and board[r+d][c+d] == 'Q')
                or (valid(r - d, c - d) and board[r-d][c-d] == 'Q'))
                    return false;
            // anti diagonal
            if ((valid(r + d, c - d) and board[r+d][c-d] == 'Q')
                or valid(r - d, c + d) and board[r-d][c+d] == 'Q')
                    return false;
        }

        // Here is a simple and better formula:
            // main diagonal share the same value of (row - col)
            // anti diagonal share the same value of (row + col)

        return true;
    }
    // notice that:
        // each row must have exactly 1 queen, so let's use it to index our recursive function
    void place_queens(int q = 0) {
        if (q == n) {
            boards.push_back(board);
            return;
        }

        int row = q;
        for (int col = 0; col < n; ++col) {
            if (free_of_attacks(row, col)) {
                board[row][col] = 'Q'; // place it
                place_queens(q + 1);
                board[row][col] = '.'; // undo placement
            }
        }
    }
    vector<vector<string>> solveNQueens(int _n) {
        n = _n;
        board = vector<string>(n, string(n, '.'));

        place_queens(0);

        return boards;
    }
};

int main() {

    return 0;
}