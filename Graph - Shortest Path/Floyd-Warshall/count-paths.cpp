// UVA 125
// https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=61
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <limits>
#include <random>
#include <cstring>
using namespace std;

void count_paths(vector<vector<int>> &graph) {
    int n = graph.size();

    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                graph[i][j] += (graph[i][k] * graph[k][j]); // combinations of paths from both sides

    // detect cycles
    for (int k = 0; k < n; ++k) {
        if (graph[k][k] > 0) // cycle
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (graph[i][k] > 0 and graph[k][j] > 0) // the path can relax on a cycle node?
                        graph[i][j] = -1;
                }
            }
    }
}

int main() {
    //freopen("data.txt", "rt", stdin);

    int m, n, test = 0, x, y;
    int cnt[31][31] = { };

    while (scanf("%d", &m) == 1) {
        memset(cnt, 0, sizeof(cnt));

        n = 0;
        while (m--) {
            scanf("%d %d", &x, &y);
            cnt[x][y]++;
            if (x > n)
                n = x;
            if (y > n)
                n = y;
        }
        n += 1;

        vector<vector<int>> graph(n, vector<int>(n));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                graph[i][j] = cnt[i][j];

        count_paths(graph);

        printf("matrix for city %d\n", test++);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (j)
                    putchar(' ');
                printf("%d", graph[i][j]);
            }
            puts("");
        }
    }
    return 0;
}

/*

6
0 1
0 2
1 2
0 3
3 4
4 3

7
0 1
0 2
0 4
2 4
2 3
3 1
4 3

5
0 2
0 1
1 5
2 5
2 1

9
0 1
0 2
0 3
0 4
1 4
2 1
2 0
3 0
3 1


5
matrix for city 0
0 1 2 -1 -1
0 0 1 0 0
0 0 0 0 0
0 0 0 -1 -1
0 0 0 -1 -1
5
matrix for city 1
0 4 1 3 2
0 0 0 0 0
0 2 0 2 1
0 1 0 0 0
0 1 0 1 0
6
matrix for city 2
0 2 1 0 0 3
0 0 0 0 0 1
0 1 0 0 0 2
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
5
matrix for city 3
-1 -1 -1 -1 -1
0 0 0 0 1
-1 -1 -1 -1 -1
-1 -1 -1 -1 -1
0 0 0 0 0



 */
