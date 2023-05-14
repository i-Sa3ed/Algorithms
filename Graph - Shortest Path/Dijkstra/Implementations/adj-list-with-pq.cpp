/// https://leetcode.com/problems/network-delay-time/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct edge {
    int w, to;
    // notice that `src` is fixed, so no need to make 'from' attribute

    bool operator < (const edge& e1) const {
        return w > e1.w; // Notice that: it must be REVERSED
    }
};

class Solution {
    int n;
    vector< vector<edge> > graph; // adj list
    int src;
    const int OO = 1e6;
public:
    vector<int> dijkstra() {
        // O((E + V) * logV) = ~O(E logV) time

        vector<int> sp(n + 1, OO);
        sp[src] = 0;

        // initialize pq
        priority_queue<edge> pq; // min heap (compare based on w)
        pq.push({0, src});

        while (!pq.empty()) {
            edge mn = pq.top();
            pq.pop();

            if (mn.w > sp[mn.to])  // use sp to check if visited or not
                continue;
            // The key idea is: once the node is visited, it's finalized..

            sp[mn.to] = mn.w;
            // relax:
            for (edge& e : graph[mn.to]) {
                // But, what about multiple edges?
                // simple, just add them and pq will choose the min based on `w`
                edge ne = {sp[mn.to] + e.w, e.to};
                pq.push(ne);
            }
        }

        return sp;
    }
    void build_graph(vector<vector<int>> times) {
        graph = vector< vector<edge> > (n + 1);
        for (auto& it : times)
            graph[it[0]].push_back({it[2], it[1]});
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
    vector< vector<int> > times = {{1, 2, 1},
                                   {2, 3, 2},
                                   {1, 3, 4}};
    int n = 3, k = 1;
    Solution solution;
    cout << solution.networkDelayTime(times, n , k);

    return 0;
}