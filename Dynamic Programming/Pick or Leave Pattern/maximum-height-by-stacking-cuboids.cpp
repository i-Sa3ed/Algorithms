#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/// https://leetcode.com/problems/maximum-height-by-stacking-cuboids/

class Solution {
    int n;
    vector<int> init = {105, 105, 105};
    unordered_map<string, int> memory;

    string encode(int idx, vector<int> vec) {
        string res = to_string(idx);
        for(int i : vec) {
            res += '.';
            res += to_string(i);
        }
        return res;
    }
    bool can_place(vector<int>& bottom, vector<int>& top) {
        for (int i = 0; i < 3; ++i) {
            if (top[i] > bottom[i])
                return false;
        }
        return true;
    }
public:
    int dp_max_height(vector<vector<int>>& cuboids, int idx, vector<int>& last) {
        /*
         * time: O(N^2)
         * memory: same (because we hash every single state)
         */
        if (idx == n)
            return 0;

        // memoization
        string state = encode(idx, last); // encode it, to be able to hash it.
        if (memory.find(state) != memory.end())
            return memory[state];
        auto& ret = memory[state];

        // next choices:
        int pick = 0;
        if (can_place(last, cuboids[idx]))
            pick = cuboids[idx][2] +                // pick the max dimension
                    dp_max_height(cuboids, idx+1, cuboids[idx]);
        int leave = dp_max_height(cuboids, idx+1, last);

        return ret = max(pick, leave);
    }
    int maxHeight(vector<vector<int>>& cuboids) {
        n = cuboids.size();
        // sort the dimensions of each cuboid
        for(auto& cuboid : cuboids)
            sort(cuboid.begin(), cuboid.end());
        // sort the cuboids itself descending (i.e. put the big cuboid first in the stack)
        sort(cuboids.rbegin(), cuboids.rend()); // N logN

        // notice that: after we sorted the cuboids
        // the solution is the longest decreasing subsequence ^_^
        // remember: LIS problem ;)

        return dp_max_height(cuboids, 0, init);
    }
};

int main() {
    vector< vector<int> > cuboids = {{50, 45, 20}, {95, 37, 53}, {45, 23, 12}};
    Solution sol;
    cout << sol.maxHeight(cuboids) << endl;

    return 0;
}