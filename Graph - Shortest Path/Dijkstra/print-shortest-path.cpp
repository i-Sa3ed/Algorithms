/// https://leetcode.com/problems/network-delay-time/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct edge {
    int w, from, to;
    // notice that `src` is fixed, so no need to make 'from' attribute
    // But if we want print the path, it will be needed :)

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
    vector<int> dijkstra(vector<int>& myParent) {
        // O((E + V) * logV) = ~O(E logV) time

        vector<int> sp(n + 1, OO);
        sp[src] = 0;

        // initialize pq
        priority_queue<edge> pq; // min heap (compare based on w)
        pq.push({0, -1, src});

        while (!pq.empty()) {
            edge mn = pq.top();
            pq.pop();

            if (mn.w > sp[mn.to])  // use sp to check if visited or not
                continue;
            // The key idea is: once the node is visited, it's finalized..

            sp[mn.to] = mn.w;
            myParent[mn.to] = mn.from;

            // relax:
            for (edge& e : graph[mn.to]) {
                // But, what about multiple edges?
                // simple, just add them and pq will choose the min based on `w`
                edge ne = {sp[mn.to] + e.w, mn.to, e.to};
                pq.push(ne);
            }
        }

        return sp;
    }
    void build_graph(vector<vector<int>> times) {
        graph = vector< vector<edge> > (n + 1);
        for (auto& it : times)
            graph[it[0]].push_back({it[2], it[0], it[1]});
    }
    void print_shortest_path(vector<int>& myParent, int target) {
        if (target == src) { // base case
            cout << target;
            return;
        }

        int parent = myParent[target];
        print_shortest_path(myParent, parent);
        cout << " -> " << target;
    }
    int networkDelayTime(vector<vector<int>>& times, int _n, int k) {
        n = _n;
        src = k;

        build_graph(times);

        vector<int> myParent(n + 1);
        vector<int> sp = dijkstra(myParent);

        print_shortest_path(myParent, 5);
        cout << endl;

        int mx = *max_element(sp.begin() + 1, sp.end()); // skip first element because it's useless
        if (mx == OO)
            return -1;
        return mx;
    }
};


int main() {
    vector< vector<int> > times;
    int n, e, k = 1;

    cin >> n >> e;
    for (int i = 0; i < e; ++i) {
        int from, to, w;
        cin >> from >> to >> w;
        times.push_back({from, to, w});
    }

    Solution solution;
    cout << solution.networkDelayTime(times, n , k);

    return 0;
}