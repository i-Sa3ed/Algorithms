#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset
#include <map>

using namespace std;

class UnionFind {
    vector<int> parent, rank;
    int forests;

    void link(int x, int y) {
        int low = x, high = y;
        if (rank[low] > rank[high])
            swap(low, high);

        parent[low] = high;
        if (rank[low] == rank[high]) // handle case of equal ranks
            ++rank[high];
    }

public:
    UnionFind(int n) {
        // initially: each node is a connected component
        parent = vector<int>(n + 1);
        rank = vector<int>(n + 1);

        forests = n;
        for (int i = 0; i <= n; ++i) {
            parent[i] = i; // initially (better than -1, for the recursive function below)
            rank[i] = 1;
        }
    }

    /// find the top parent
    // recursive version:
    int find_and_compress(int x) {
        if (x == parent[x]) // reached the top parent
            return x;
        // do the compression recursively
        return parent[x] = find_and_compress(parent[x]);
    }
    // iterative version:
    int find_iter(int x) {
        vector<int> path; // save the path to the top parent
        while (x != parent[x]) {
            path.push_back(x);
            x = parent[x];
        }

        // compress:
        for (int& node : path)
            parent[node] = x;

        return x;
    }


    bool Union(int x, int y) {
        x = find_and_compress(x), y = find_and_compress(y); // obtain the top parents
        if (x != y) {
            link(x, y);
            --forests;
        }

        return (x != y); // are they in different CCs?
    }
};

/// challenge
// use 'cc_size' instead of 'cc_size'
// provide `current_cc_state`
class UnionFind2 {
    vector<int> parent, cc_size;
    int forests;

    void link(int x, int y) {
        int low = x, high = y;
        if (cc_size[low] > cc_size[high])
            swap(low, high);

        parent[low] = high;
        cc_size[high] += cc_size[low]; // add child's size to its parent
    }

public:
    UnionFind2(int n) {
        // initially: each node is a connected component
        parent = vector<int>(n + 1);
        cc_size = vector<int>(n + 1);

        forests = n;
        for (int i = 0; i <= n; ++i) {
            parent[i] = i; // initially (better than -1, for the recursive function below)
            cc_size[i] = 1; // each node is a cc by itself
        }
    }

    /// find the top parent
    // recursive version:
    int find_and_compress(int x) {
        if (x == parent[x]) // reached the top parent
            return x;
        // do the compression recursively
        return parent[x] = find_and_compress(parent[x]);
    }
    // iterative version:
    int find_iter(int x) {
        vector<int> path; // save the path to the top parent
        while (x != parent[x]) {
            path.push_back(x);
            x = parent[x];
        }

        // compress:
        for (int& node : path)
            parent[node] = x;

        return x;
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

    vector< vector<int> > current_cc_state() {
        int n = parent.size() - 1;
        vector< vector<int> > list(n + 1);
        for (int node = 0; node <= n; ++node) {
            int par = find_and_compress(node);
            list[par].push_back(node);
        }

        // copy non-empty CCs
        vector< vector<int> > actual_cc;
        for (auto& cc : list)
            if (cc.size())
                actual_cc.push_back(cc);

        return actual_cc;
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
    vector<edge> mstEdges;
    int mstCost = 0;

    sort(edgeList.begin(), edgeList.end());

    for (edge& e : edgeList) {
        if (uf.Union(e.from, e.to)) {
            // cross edge
            mstEdges.push_back(e);
            mstCost += e.w;
        }
    }

    bool full_mst = (mstEdges.size() == n-1);
    return mstCost;
}

//////////////// test & main ////////////////

void test() {
    int n; cin >> n; // 5
    UnionFind2 uf2(n);

    uf2.Union(0, 1);
    uf2.Union(4, 3);

    vector< vector<int> > cc = uf2.current_cc_state();

}
int main() {
    test();

    return 0;
}