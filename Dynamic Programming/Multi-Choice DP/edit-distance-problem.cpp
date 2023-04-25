#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

/// https://leetcode.com/problems/edit-distance/


const int MAX = 505;
int memory[MAX][MAX];
class Solution {
    int N, M;
    string s1, s2;
public:
    int dp_edit_distance(int idx1 = 0, int idx2 = 0) {
        if (idx1 == N)
            return (M - idx2);
        if (idx2 == M)
            return (N - idx1);

        auto& ret = memory[idx1][idx2];
        if (ret != -1)
            return ret;

        if (s1[idx1] == s2[idx2])
            return dp_edit_distance(idx1 + 1, idx2 + 1); // skip
        // 3 possible operations: apply all of them at word1
        int insert = 1 + dp_edit_distance(idx1, idx2 + 1); // insertion of s2[idx2], then s1[idx1] == s2[idx2], then we can skip them.
        int del = 1 + dp_edit_distance(idx1 + 1, idx2);
        int change = 1 + dp_edit_distance(idx1 + 1, idx2 + 1);

        return ret = min({insert, del, change});
    }
    int minDistance(string word1, string word2) {
        memset(memory, -1, sizeof(memory));
        s1 = word1, N = word1.size();
        s2 = word2, M = word2.size();

        return dp_edit_distance();
    }
};

int main() {

    return 0;
}