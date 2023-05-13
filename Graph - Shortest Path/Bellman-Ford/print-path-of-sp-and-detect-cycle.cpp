#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset
#include <map>

using namespace std;

struct edge {
    int from, to, w;
    edge(int from, int to, int w) : from(from), to(to), w(w) { }
};

void build_path(vector<int>& prev, int target, vector<int>& path) {
    int p = prev[target];
    if (p == -1) {
        path.push_back(target);
        return;
    }

    build_path(prev, p, path);
    path.push_back(target);
}
bool bellman(vector<edge>& edgeList, int n, int src, vector<int>& sp, vector<int>& prev) {
    const int OO = 1e6;
    sp = vector<int>(n + 1, OO); // from src to each node (1-based)
    prev = vector<int>(n + 1, -1); // -1 = doesn't have coming edge yet
    sp[src] = 0;

    // tabulation:
    /// Notice that: the algorithm is very sensitive to the order of the edge list!
    for (int e = 1; e <= n; ++e) { // notice, iterate N iterations (one extra to detect the cycle)
        bool any_change_happened = false;
        for (auto &edge: edgeList) {
            if (sp[edge.to] > sp[edge.from] + edge.w) {
                sp[edge.to] = sp[edge.from] + edge.w;
                prev[edge.to] = edge.from; // update the coming node
                any_change_happened = true;
            }
        }
        if (!any_change_happened) // this means => all nodes are explored and also have their min sp
            break;

        // detect cycle:
        // the normal graph should find the paths in only N-1 edges
        // if we iterate more and still have another shorter path => cycle
        if (e == n)
            return true;
    }

    return false;
}

int main() {
    int n = 4;
    vector<edge> edgeList = {{2, 1, 1},
                             {2, 3, 1},
                             {3, 4, 1}};
    vector<int> prev;
    vector<int> sp;
    bool has_cycle = bellman(edgeList, n, 2, sp, prev);

    vector<int> path;
    build_path(prev, 4, path);

    for (int i : path)
        cout << i << ' ';
    cout << endl;

    return 0;
}