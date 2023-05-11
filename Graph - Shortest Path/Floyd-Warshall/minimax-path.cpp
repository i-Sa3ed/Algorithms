// UVA 534 - Frogger
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=475
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <limits>
#include <random>
#include <cstring>
using namespace std;

void compute_min_max(vector<vector<int>> &graph) {
    int n = graph.size();

    for (int k = 0; k < n; ++k) {
        // we are just allowed to use the first k nodes as intermediate ones
        for (int from = 0; from < n; ++from) {
            for (int to = 0; to < n; ++to) {
                int new_minimax = max(graph[from][k], graph[k][to]);
                graph[from][to] = min(graph[from][to], new_minimax);
            }
        }
    }
}

int main() {
    //freopen("data.txt", "rt", stdin);

    for (int test = 1;; test++) {
        int n;
        cin >> n;

        if (n == 0)
            break;

        vector<int> x(n), y(n);
        vector<vector<int>> graph(n, vector<int>(n));

        for (int i = 0; i < n; ++i)
            cin >> x[i] >> y[i];

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                int dx = x[i] - x[j], dy = y[i] - y[j];
                graph[i][j] = dx * dx + dy * dy;
            }

        compute_min_max(graph);

        printf("Scenario #%d\nFrog Distance = %.3lf\n\n", test, sqrt(graph[0][1]));
    }
    return 0;

}
