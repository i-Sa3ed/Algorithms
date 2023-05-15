/// https://leetcode.com/problems/similar-string-groups/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset
#include <map>

using namespace std;

class UnionFind2 {
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
    UnionFind2(int n) {
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
        vector< vector<int> > list(n);
        for (int node = 0; node < n; ++node) {
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
    int count_cc() {
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
    UnionFind2 uf2(n);

    sort(edgeList.begin(), edgeList.end());

    for (edge& e : edgeList) {
        uf2.Union(e.from, e.to);
    }

    vector< vector<int> > tmp = uf2.current_cc_state();

    return uf2.count_cc();
}

class Solution {
    int n;
    vector<string> strs;
public:
    bool similar(int i, int j) {
        int mismatch = 0;
        int len = strs[i].size();
        for (int k = 0; k < len; ++k) {
            if (strs[i][k] != strs[j][k])
                ++mismatch;
            if (mismatch > 2) // improve time by early return
                return false;
        }

        return mismatch == 2; // or mismatch == 0, but it's impossible because we ignored the identical ;)
    }
    int numSimilarGroups(vector<string>& _strs) {
        strs = _strs;
        sort(strs.begin(), strs.end());
        n = unique(strs.begin(), strs.end()) - strs.begin(); // ignore the identical words

        vector<edge> edgeList;
        for (int from = 0; from < n; ++from) {
            for (int to = from + 1; to < n; ++to) {
                if (similar(from, to))
                    edgeList.push_back({from, to});
            }
        }

        return Kruskal(edgeList, n);
    }
};

int main() {
    vector<string> strs = {"dzqsu","udzqs","qzsud","sudzq","zsduq","duszq","sduqz","suqzd","szqdu","qzuds","dzqsu","uqdzs","zsduq","quzds"};
    Solution solution;
    cout << solution.numSimilarGroups(strs) << endl;

    return 0;
}