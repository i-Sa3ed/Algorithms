#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset

using namespace std;

/// https://leetcode.com/problems/longest-palindromic-substring/

const int MAX = 1001 + 1;
short memory[MAX][MAX];	// values only -1, 0, 1. We can represent in other ways
string str;

int isPalindrome(int start, int end) {	// O(n^2)
    if (start >= end)	// range is done
        return 1;		// single letter or empty string are palindromes

    auto &ret = memory[start][end];
    if (ret != -1)
        return ret;

    if (str[start] == str[end])
        return ret = isPalindrome(start + 1, end - 1);

    return ret = 0;
}
class Solution {
public:
    string longestPalindrome(string s) {
        str = s;
        memset(memory, -1, sizeof(memory));

        int idx = -1, length = 0, sz = (int) s.size();

        // Try all ranges and pick the longest
        // Think in any recursive call as O(1)
        // So this 2 nested are O(n^2)
        for (int i = 0; i < sz; ++i) {
            for (int j = i; j < sz; ++j) {
                int len = j - i + 1;
                if (isPalindrome(i, j) && len > length)
                    idx = i, length = len;
            }
        }
        return s.substr(idx, length);
    }
};

int main() {
    Solution sol;
    cout << sol.longestPalindrome("ac");
    return 0;
}