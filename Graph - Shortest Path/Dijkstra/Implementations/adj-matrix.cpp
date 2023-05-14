/// https://leetcode.com/problems/network-delay-time/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    int n;
    vector< vector<int> > graph; // adj matrix
    int src;
    const int OO = 1e6;
public:

    vector<int> dijkstra() { // O(n^2) time - O(n) memory
        vector<int> sp(n + 1, OO);
        sp[src] = 0;
        vector<bool> visited (n + 1);
        visited[src] = true;

        int mnW, mnNode;

        while (true) {
            mnW = OO;
            // pick the node with min weight
            for (int node = 1; node <= n; ++node) {
                if (!visited[node] and graph[src][node] < mnW)
                    mnW = graph[src][node], mnNode = node;
            }
            if (mnW == OO) // didn't find any connected node
                break;

            sp[mnNode] = graph[src][mnNode]; // get the sp for the chosen node
            // relax the nodes connected to the chosen node:
            for (int ne = 1; ne <= n; ++ne) {
                graph[src][ne] = min(graph[src][ne], sp[mnNode] + graph[mnNode][ne]);
            }
            visited[mnNode] = true; // remove it virtually
        }

        return sp;
    }
    void build_graph(vector<vector<int>> times) {
        graph = vector< vector<int> > (n + 1, vector<int>(n + 1, OO));
        for (auto& it : times)
            graph[it[0]][it[1]] = it[2];
    }
    int networkDelayTime(vector<vector<int>>& times, int _n, int k) {
        n = _n;
        src = k;

        build_graph(times);

        vector<int> sp = dijkstra();
        int mx = *max_element(sp.begin() + 1, sp.end()); // skip first element because it's useless
        if (mx == OO)
            return -1;
        return mx;
    }
};


int main() {
    int n, e;
    cin >> n >> e;

    vector< vector<int> > times;
    for (int i = 0; i < e; ++i) {
        int f, t, w;
        cin >> f >> t >> w;
        times.push_back({f, t, w});
    }

    Solution solution;
    cout << solution.networkDelayTime(times, n, 5);

    return 0;
}