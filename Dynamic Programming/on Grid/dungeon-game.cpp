#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset

using namespace std;

/// https://leetcode.com/problems/dungeon-game/

const int MAX = 200;
int memory[MAX][MAX];

class Solution {
    vector<vector<int>> dungeon;
    int n, m;
public:
    int dp_min_health(int i = 0, int j = 0) {
        if (i >= n or j >= m)
            return INT_MAX/2; // out of boundary => avoid it
        else if (i == n-1 and j == m-1)
            return max(1, -dungeon[i][j] + 1);

        auto& ret = memory[i][j];
        if (ret != -1)
            return ret;

        // next moves
        int path1 = max(1, dp_min_health(i, j + 1) - dungeon[i][j]); // to the right
        int path2 = max(1, dp_min_health(i + 1, j) - dungeon[i][j]);

        return ret = min(path1, path2);
    }
    int calculateMinimumHP(vector<vector<int>>& _dungeon) {
        memset(memory, -1, sizeof(memory));
        dungeon = _dungeon;
        n = dungeon.size(), m = dungeon[0].size();

        return dp_min_health();
    }
};

int main() {

    return 0;
}