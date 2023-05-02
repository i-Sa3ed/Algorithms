#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset
#include <cassert>

using namespace std;

// choose the best split in order to minimize the total #operations

struct matrix{ int rows = 0, cols = 0; };

const int MAX = 1000;
int memory[MAX][MAX];
vector<matrix> matrices;

int evaluate(matrix mat1, matrix mat2) {
    return mat1.rows * mat1.cols * mat2.cols;
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
        ret = min(ret, evaluate(mat1, mat2) + dp_min(startIdx, k) + dp_min(k + 1, endIdx));
    }

    return ret;
}
int min_operations(vector<matrix>& chain) {
    memset(memory, -1, sizeof(memory));
    matrices = chain;

    return dp_min(0, matrices.size() - 1);
}

int main() {
    vector<matrix> mats = {{1, 2}, {2, 3}, {3, 4}};
    assert(min_operations(mats) == 18);

    /*mats = {{5, 10}, {10, 19}, {19, 7}};
    assert(min_operations(mats) == 1615);*/

    return 0;
}