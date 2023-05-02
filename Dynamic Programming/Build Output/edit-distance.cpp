#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

/// https://leetcode.com/problems/edit-distance/
// this is the original problem
// we will add the feature of printing the changes that occurred.


const int MAX = 505;
int memory[MAX][MAX];
class Solution {
    int N, M;
    string s1, s2;
    int answer;
public:
    int dp_edit_distance(int idx1 = 0, int idx2 = 0) {
        if (idx1 == N)
            return (M - idx2); // insert the remaining of word2
        if (idx2 == M)
            return (N - idx1); // delete the rest of word1

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
    void dp_print_edits(int idx1 = 0, int idx2 = 0) {
        if (idx1 == N) {
            if (idx2 < M)
                cout << "In " << s1 << ": insert the remaining of word2 from index " << idx2 << " to the end\n";
            return;
        }
        else if (idx2 == M) {
            if (idx1 < N)
                cout << "In " << s1 << ": delete the rest of word1 from index " << idx1 << " to the end\n";
            return;
        }

        int optimal = dp_edit_distance(idx1, idx2);
        if (idx1 == 0 and idx2 == 0)
            answer = optimal;

        if (s1[idx1] == s2[idx2]) {
            dp_print_edits(idx1 + 1, idx2 + 1); // skip
            return;
        }

        // 3 possible operations: apply all of them at word1
        int insert = 1 + dp_edit_distance(idx1, idx2 + 1);
        int del = 1 + dp_edit_distance(idx1 + 1, idx2);

        if (insert == optimal) {
            cout << "In " << s1 << ": insert letter " << s2[idx2] << " at index " << idx1 << "\n";
            dp_print_edits(idx1, idx2 + 1);
        }
        else if (del == optimal) {
            cout << "In " << s1 << ": delete letter " << s1[idx1] << " from index " << idx1 << "\n";
            dp_print_edits(idx1 + 1, idx2);
        }
        else { // change
            cout << "In " << s1 << ": change letter " << s1[idx1] << " at index " << idx1 << " to letter " << s2[idx2] <<"\n";
            dp_print_edits(idx1 + 1, idx2 + 1);
        }
    }

    int minDistance(string word1, string word2) {
        memset(memory, -1, sizeof(memory));
        s1 = word1, N = word1.size();
        s2 = word2, M = word2.size();

        cout << "Steps for '" << s1 << "' to '" << s2 << "'\n";
        dp_print_edits();
        return answer;
    }
};

int main() {
    Solution s1;
    cout << s1.minDistance("xy", "axy") << " steps in total\n\n";
    cout << s1.minDistance("axy", "xy") << " steps in total\n\n";
    cout << s1.minDistance("axy", "bxy") << " steps in total\n\n";
    cout << s1.minDistance("axy", "a") << " steps in total\n\n";
    cout << s1.minDistance("a", "axy") << " steps in total\n\n";
    cout << s1.minDistance("axy", "axy") << " steps in total\n\n";

    cout << s1.minDistance("horse", "ros") << " steps in total\n\n";
    cout << s1.minDistance("park", "spake") << " steps in total\n\n";
    cout << s1.minDistance("spake", "park") << " steps in total\n\n";
    cout << s1.minDistance("spakehz", "park") << " steps in total\n\n";

    return 0;
}