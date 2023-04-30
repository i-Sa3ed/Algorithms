#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset

using namespace std;

/// https://leetcode.com/problems/binary-trees-with-factors/

const int MAX = 1000, mod = 1e9 + 7;
long long memory[MAX];

class Solution {
    vector<int> arr;
    int n;
    unordered_map<int, int> valToIdx;
public:
    long long dp_count(int root_idx) {
        auto& ret = memory[root_idx];
        if (ret != -1)
            return ret;
        
        // next choices
        ret = 1; // 1-node tree (i.e. the root only)
        for (int child = 0; child < root_idx; ++child) {
            int child2 = -1;
            if (arr[root_idx] % arr[child] == 0) {
                int val = arr[root_idx] / arr[child];
                if (valToIdx.find(val) != valToIdx.end())
                    child2 = valToIdx[val];
            }

            if (child2 != -1) {
                long long add = (dp_count(child) % mod * dp_count(child2) % mod) % mod;
                ret += add;
            }
        }

        return ret;
    }
    int numFactoredBinaryTrees(vector<int>& _arr) {
        arr = _arr;
        n = arr.size();
        sort(arr.begin(), arr.end());
        memset(memory, -1, sizeof(memory));

        for (int i = 0; i < n; ++i) {
            valToIdx[arr[i]] = i;
        }
        
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            ans += dp_count(i);
            ans %= mod;
        }

        return ans;
    }
};

int main() {

    return 0;
}