#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset
#include <cassert>

using namespace std;

/// https://leetcode.com/problems/edit-distance/

const int MAX = 505;
int memory[MAX][MAX];
class Solution {
    int N, M;
public:
    // helper function
    int answer(int i1, int i2) {
        if (i1 < 0 or i2 < 0)
            return max(i1, i2) + 1;

        assert(memory[i1][i2] != -1);
        return memory[i1][i2];
    }
    int minDistance(string word1, string word2) {
        memset(memory, -1, sizeof(memory));
        N = word1.size();
        M = word2.size();

        if (N == 0 or M == 0) // empty strings, special case
            return max(N, M);

        for (int idx1 = 0; idx1 < N; ++idx1) {
            for (int idx2 = 0; idx2 < M; ++idx2) {
                int& distance = memory[idx1][idx2];
                if (word1[idx1] == word2[idx2])
                    distance = answer(idx1 - 1, idx2 - 1);
                else {
                    int insert = 1 + answer(idx1, idx2 - 1);
                    int del = 1 + answer(idx1 - 1, idx2);
                    int change = 1 + answer(idx1 - 1, idx2 - 1);

                    distance = min({insert, del, change});
                }
            }
        }

        return memory[N-1][M-1];
    }
};

int main() {
    Solution solution;
    cout << solution.minDistance("horse", "ros");

    return 0;
}