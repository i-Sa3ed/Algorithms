/// https://leetcode.com/problems/number-of-operations-to-make-network-connected/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset
#include <map>

using namespace std;

class UnionFind {
    vector<int> parent, cc_size;
    int n;
    int forests;

    void link(int x, int y) {
        int low = x, high = y;
        if (cc_size[low] > cc_size[high])
            swap(low, high);

        parent[low] = high;
        cc_size[high] += cc_size[low]; // add child's size to its parent
    }

public:
    UnionFind(int n) {
        // initially: each node is a connected component
        n = n;
        parent = vector<int>(n);
        cc_size = vector<int>(n);

        forests = n;
        for (int i = 0; i < n; ++i) {
            parent[i] = i; // initially (better than -1, for the recursive function below)
            cc_size[i] = 1; // each node is a cc by itself
        }
    }

    // find the top parent
    int find_and_compress(int x) {
        if (x == parent[x]) // reached the top parent
            return x;
        // do the compression recursively
        return parent[x] = find_and_compress(parent[x]);
    }

    bool Union(int x, int y) {
        // obtain the top parents
        x = find_and_compress(x);
        y = find_and_compress(y);

        if (x != y) {
            link(x, y);
            --forests;
        }

        return (x != y); // are they in different CCs?
    }

    int count_cc() {
        // number of sub-MSTs
        return forests;
    }
};

struct edge {
    int from, to, w = 0;

    bool operator < (const edge& e) const {
        return w < e.w; // notice: it's not a PQ ;) => normal logic
    }
};
int Kruskal(vector<edge>& edgeList, int n) {
    UnionFind uf(n);

    // no need to sort, we only care about connectivity
    //sort(edgeList.begin(), edgeList.end());

    for (edge& e : edgeList) {
        uf.Union(e.from, e.to);
    }

    return uf.count_cc();
}

class Solution {
    int n;
public:
    int makeConnected(int _n, vector<vector<int>>& connections) {
        n = _n;

        if (connections.size() < n-1) // not enough
            return -1;

        // build edge list
        vector<edge> edgeList;
        for (auto& c : connections)
            edgeList.push_back({c[0], c[1]});

        int sub_MSTs = Kruskal(edgeList, n);
        return (sub_MSTs - 1);
    }
};

int main() {

    return 0;
}