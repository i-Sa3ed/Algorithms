#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset

using namespace std;

/// https://leetcode.com/problems/sudoku-solver/

class Solution {
    struct cell {int i, j; };
    vector<cell> emptyCells;

    // use them to mark the reserved cells
    int row_memory[10][10], col_memory[10][10], block_memory[3][3][10];

    vector<vector<char>> board;
    bool done = false;
public:
    bool can_place(int r, int c, int d) {
        return !row_memory[r][d] and !col_memory[c][d] and !block_memory[r / 3][c / 3][d];
    }
    void update_memory(int r, int c, int d, int val) {
        row_memory[r][d] = col_memory[c][d] = block_memory[r / 3][c / 3][d] = val;
    }

    void solve_cell(int empIdx = 0) {
        if (empIdx == emptyCells.size())  {// successfully filled all empty cells
            done = true;
            return;
        }

        cell cur = emptyCells[empIdx];

        char& toFill = board[cur.i][cur.j];
        for (int d = 1; d <= 9; ++d) {
            if (can_place(cur.i, cur.j, d)) {
                toFill = char(d + '0'); // assign
                update_memory(cur.i, cur.j, d, 1);

                solve_cell(empIdx + 1);
                if (done)
                    return;

                update_memory(cur.i, cur.j, d, 0);
                toFill = '.'; // undo
            }
        }
    }
    void solveSudoku(vector<vector<char>>& _board) {
        board = _board;
        memset(row_memory, 0, sizeof(row_memory));
        memset(col_memory, 0, sizeof(col_memory));
        memset(block_memory, 0, sizeof(block_memory));

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') {
                    emptyCells.push_back({i, j});
                }
                else {
                    int int_val = board[i][j] - '0';
                    row_memory[i][int_val] = 1;
                    col_memory[j][int_val] = 1;
                    block_memory[i/3][j/3][int_val] = 1;
                }
            }
        }

        solve_cell();

        _board = board;
    }
};

int main() {

    return 0;
}