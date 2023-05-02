#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset
#include <cassert>

using namespace std;

// choose the best split in order to minimize the total #operations

struct matrix{ int rows = 0, cols = 0; };

const int MAX = 100 + 1;
int memory[MAX][MAX];
int bracket[MAX][MAX]; // to save the optimal choice (i.e. k)

vector<matrix> matrices;
int answer;

int evaluate(matrix mat1, matrix mat2) {
    return mat1.rows * mat1.cols * mat2.cols;
}
char to_char(int idx) {
    assert(idx < 26);
    return char('A' + idx);
}

int dp_min(int startIdx, int endIdx) { // O(N^3) time - O(N^2) memory
    if (startIdx == endIdx)
        return 0;

    auto& ret = memory[startIdx][endIdx];
    if (ret != -1)
        return ret;

    ret = INT_MAX;
    for (int k = startIdx; k < endIdx; ++k) {
        matrix mat1 = {matrices[startIdx].rows, matrices[k].cols};
        matrix mat2 = {matrices[k + 1].rows, matrices[endIdx].cols};

        int split = evaluate(mat1, mat2) + dp_min(startIdx, k) + dp_min(k + 1, endIdx);
        if (ret > split) {
            ret = split;
            bracket[startIdx][endIdx] = k; // save the optimal choice!
        }
    }

    return ret;
}
void dp_print_with_brackets(int startIdx, int endIdx) {
    // this function prints the matrices as capital letters [A .. Z]
    // assuming that we have 26 matrices at most

    if (startIdx == endIdx) {
        cout << to_char(startIdx);
        return;
    }

    int optimal = dp_min(startIdx, endIdx);
    if (startIdx == 0 and endIdx == matrices.size() - 1) // first call
        answer = optimal;

    int k = bracket[startIdx][endIdx];
    cout << "(";
    // print the first split
    dp_print_with_brackets(startIdx, k);
    // print the second split
    dp_print_with_brackets(k + 1, endIdx);
    cout << ")";
}
int min_operations(vector<matrix>& chain) {
    memset(memory, -1, sizeof(memory));
    matrices = chain;

    dp_print_with_brackets(0, matrices.size() - 1);

    return answer;
}

int main() {
    vector<matrix> mats = {{1, 2}, {2, 3}, {3, 4}};
    min_operations(mats);
    cout << endl;

    mats = {{2, 3}};
    min_operations(mats);
    cout << endl;

    mats = {{ 5, 10 } , { 10, 19 } , { 19, 7 } , { 7, 5 }};
    min_operations(mats);
    cout << endl;

    mats = {{ 40, 20} , { 20, 30 } , { 30, 10 } , { 10, 30 }};
    min_operations(mats);
    cout << endl;

    return 0;
}