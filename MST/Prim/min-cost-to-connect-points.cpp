#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;


/// Prim + add `done` counter

class Solution {
    struct edge {
        int from; // to print the edges
        int toIdx, c; // destination, cost

        bool operator < (const edge& e) const {
            return c > e.c; // reversed
        }
    };
    int n;
    vector< vector<int> > points;
public:
    int prim() {
        priority_queue<edge> pq;
        pq.push({-1, 0, 0}); // base case
        vector<bool> processed(n + 1);

        int cost = 0;
        /// Expected time improvement: use variable to stop the loop
        int done = 0;
        while (!pq.empty()) {
            edge cross = pq.top();
            pq.pop();

            if (processed[cross.toIdx]) // handle multiple edges
                continue;
            // why we can't use sp array to handle it (like Dijkstra)?
            // b. we don't accumulate the costs, we are just compare single edges...

            cost += cross.c;
            processed[cross.toIdx] = true;
            ++done;

            if (done == n)
                break;

            // bring cross's neighbors
            for (int i = 0; i < n; ++i) {
                if (processed[i])
                    continue;

                int tmpCost = manhattan(cross.toIdx, i);
                pq.push({cross.toIdx, i, tmpCost});
            }
        }

        return cost;
    }
    int prim(vector< vector<int> >& mst_edges) {
        priority_queue<edge> pq;
        pq.push({-1, 0, 0}); // base case
        vector<bool> processed(n + 1);

        int cost = 0;
        /// Expected time improvement: use variable to stop the loop
        int done = 0;
        while (!pq.empty()) {
            edge cross = pq.top();
            pq.pop();

            if (processed[cross.toIdx]) // handle multiple edges
                continue;
            // why we can't use sp array to handle it (like Dijkstra)?
            // b. we don't accumulate the costs, we are just compare single edges...

            cost += cross.c;
            processed[cross.toIdx] = true;
            if (cross.from != -1)
                mst_edges.push_back({cross.from, cross.toIdx});
            ++done;

            if (done == n)
                break;

            // bring cross's neighbors
            for (int i = 0; i < n; ++i) {
                if (processed[i])
                    continue;

                int tmpCost = manhattan(cross.toIdx, i);
                pq.push({cross.toIdx, i, tmpCost});
            }
        }

        return cost;
    }
    int manhattan(int i1, int i2) {
        int dx = abs(points[i1][0] - points[i2][0]),
                dy = abs(points[i1][1] - points[i2][1]);
        return (dx + dy);
    }
    int minCostConnectPoints(vector<vector<int>>& _points) {
        points = _points;
        n = points.size();

        vector< vector<int> > mst_edges;
        int mst = prim(mst_edges);
        for (auto& edge : mst_edges)
            cout << edge[0] << ' ' << edge[1] << endl;
        cout << endl;
        return mst;
    }
};

int main() {
    Solution solution;
    vector< vector<int> > points = {{0, 0},
                                    {2, 2},
                                    {3, 10},
                                    {5, 2},
                                    {7, 0}};
    cout << solution.minCostConnectPoints(points);

}