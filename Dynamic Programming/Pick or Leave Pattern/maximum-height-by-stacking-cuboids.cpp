#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

/// https://leetcode.com/problems/maximum-height-by-stacking-cuboids/

const int MAX = 100 + 1;
int memory[MAX][MAX];

class Solution {
    int n;

    bool can_place(vector<int>& bottom, vector<int>& top) {
        for (int i = 0; i < 3; ++i) {
            if (top[i] > bottom[i])
                return false;
        }
        return true;
    }
public:
    int dp_max_height(vector<vector<int>>& cuboids, int idx, int last) {
        /*
         * time: O(N^2)
         * memory: same
         */
        if (idx == n)
            return 0;

        // memoization
        auto& ret = memory[idx][last];
        if (ret != -1)
            return ret;

        // next choices:
        int pick = 0;
        if (last == n or can_place(cuboids[last], cuboids[idx]))
            pick = cuboids[idx][2] +                // pick the max dimension
                    dp_max_height(cuboids, idx+1, idx);
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

        memset(memory, -1, sizeof(memory));
        return dp_max_height(cuboids, 0, n);
    }
};

int main() {
    vector< vector<int> > cuboids = {{50, 45, 20}, {95, 37, 53}, {45, 23, 12}};
    Solution sol;
    cout << sol.maxHeight(cuboids) << endl;

    return 0;
}