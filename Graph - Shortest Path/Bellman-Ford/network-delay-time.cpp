/// https://leetcode.com/problems/network-delay-time/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset
#include <map>

using namespace std;

class Solution {
    struct edge {
        int from, to, w;
        edge(int from, int to, int w) : from(from), to(to), w(w) { }
    };

    int n;
    int src;
    const int OO = 1e6;
public:
    int bellman(vector<edge>& edgeList) {
        vector<int> sp(n + 1, OO); // from src to each node (1-based)
        sp[src] = 0;

        // tabulation:
        for (int e = 1; e <= n-1; ++e) {
            bool any_change_happened = false;
            for (auto& edge : edgeList) {
                if (sp[edge.to] > sp[edge.from] + edge.w) {
                    sp[edge.to] = sp[edge.from] + edge.w;
                    any_change_happened = true;
                }
            }
            if (!any_change_happened) // this means => all nodes are explored and also have their min sp
                break;
        }

        // find the max delay (which is the min for all nodes)
        int ret = 0;
        for (int i = 1; i <= n; ++i)
            ret = max(ret, sp[i]);
        return ret;
    }
    int networkDelayTime(vector<vector<int>>& times, int _n, int k) {
        n = _n;
        src = k;
        vector<edge> edgeList;
        for (auto time : times)
            edgeList.push_back(edge(time[0], time[1], time[2]));

        int min_for_all = bellman(edgeList);
        if (min_for_all == OO)
            return -1;
        return min_for_all;
    }
};

int main() {
    Solution solution;
    vector<vector<int>> times = {{2, 1, 1},
                         {2, 3, 1},
                         {3, 4, 1}};
    cout << solution.networkDelayTime(times, 4, 2);

    return 0;
}