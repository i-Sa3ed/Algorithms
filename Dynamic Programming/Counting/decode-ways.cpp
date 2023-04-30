#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset

using namespace std;

/// https://leetcode.com/problems/decode-ways/

const int MAX = 100;
int memory[MAX];

class Solution {
    string s;
    int n;
public:
    bool possible_2_digits(int i) {
        string tmp = s.substr(i, 2);
        return (stoi(tmp) <= 26);
    }
    int dp_count(int idx = 0) {
        // check for leading 0s first of all ;)
        if (s[idx] == '0') // invalid path
            return 0;
        if (idx >= n - 1) // reach a leaf?
            return 1;

        auto& ret = memory[idx];
        if (ret != -1)
            return ret;

        // next
        ret = dp_count(idx + 1); // take 1 digit
        if (possible_2_digits(idx))
            ret += dp_count(idx + 2);

        return ret;
    }
    int numDecodings(string str) {
        s = str;
        n = s.size();
        memset(memory, -1, sizeof(memory));

        // final answer = number of valid leaves in the recursion tree.
        return dp_count();
    }
};

int main() {
    Solution solution;
    string str; cin >> str;
    cout << solution.numDecodings(str);

    return 0;
}