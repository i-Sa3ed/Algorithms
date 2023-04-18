#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/// https://leetcode.com/problems/longest-common-subsequence/
string str1, str2;
vector< vector<int> > memory;
int lcs(int idx1 = 0, int idx2 = 0) {
    /*
     * time: O(n*m) [n = size of str1, m = size of str2]
     * memory: O(n*m)
     */

    if (idx1 == str1.size() or idx2 == str2.size())
        return 0;
    
    // memoization:
    int &ret = memory[idx1][idx2];
    if (ret != -1)
        return ret;

    // next choices:
    if (str1[idx1] == str2[idx2]) // pick both
        ret = 1 + lcs(idx1 + 1, idx2 + 1);
    else {
        // leave one of them each time
        ret = max(lcs(idx1+1, idx2), lcs(idx1, idx2+1));
    }

    return ret;
}
int longestCommonSubsequence(string text1, string text2) {
    str1 = text1, str2 = text2;
    int mx = max(text1.size(), text2.size());
    memory = vector< vector<int> >(mx, vector<int>(mx, -1));
    return lcs();
}

int main() {
    
    return 0;
}