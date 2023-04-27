#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset

using namespace std;
/// https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/

const int MAX = 500;
int memory[MAX][MAX];

class Solution {
    int n;
    string str;

public:
    int dp_min_ops(int left, int right) {
        if (left >= right) {
            return 0;
        }

        auto& ret = memory[left][right];
        if (ret != -1)
            return ret;

        // next
        if (str[left] == str[right])
            ret = dp_min_ops(left + 1, right - 1); // no need to do any operations
        else {
            int insert1 = 1 + dp_min_ops(left + 1, right),
                insert2 = 1 + dp_min_ops(left, right - 1);
            ret = min(insert1, insert2);
        }
        return ret;
    }
    int minInsertions(string s) {
        memset(memory, -1, sizeof(memory));
        n = s.size();
        str = s;

        return dp_min_ops(0, n - 1);
    }
};

int main() {
    Solution sol;
    cout << sol.minInsertions("zjveiiwvc") << endl;

    return 0;
}