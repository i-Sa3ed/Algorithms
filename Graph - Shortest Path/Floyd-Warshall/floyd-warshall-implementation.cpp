#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset
#include <map>

using namespace std;

// we can trivially implement it using memoization..
// Tabulation code: more efficient, especially when it comes to memory

typedef vector< vector<int> > Matrix;
const int OO = 1e9;

void print(Matrix& graph) {
    int n = graph.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (graph[i][j] == OO)
                cout << "OO ";
            else
                cout << graph[i][j] << ' ';
        }
        cout << endl;
    }
}
void print_path(Matrix& path, int from, int to) {
    // it assumes that the path is already exists

    int k = path[from][to];
    if (k == -1) { // last edge
        cout << from << ' ' << to << endl;
        return;
    }

    print_path(path, from, k);
    print_path(path, k, to);
}
void floyd_shortest_path(Matrix& graph, Matrix& path) {
    int n = graph.size();

    for (int k = 0; k < n; ++k) {
        // we are just allowed to use the first k nodes as intermediate ones
        for (int from = 0; from < n; ++from) {
            for (int to = 0; to < n; ++to) {
                int relax = graph[from][k] + graph[k][to];
                if (relax < graph[from][to]) {
                    graph[from][to] = relax;
                    path[from][to] = k; // move: from => k, then: k => to
                }
            }
        }

        cout << "\n*********************\n";
        cout << "After relaxing with " << k << endl;
        print(graph);
    }
}

int main() {
    int n, e;
    cin >> n >> e;

    Matrix graph(n, vector<int>(n, OO)); // weighted graph (adj matrix)
    // initialize the diagonal (self loops) with 0:
    for (int i = 0; i < n; ++i) {
        graph[i][i] = 0;
    }
    for (int edge = 0; edge < e; ++edge) {
        int from, to, w;
        cin >> from >> to >> w;
        if (from != to)
            graph[from][to] = min(graph[from][to], w); // take the min between repeated edges
    }

    // -1 => for direct link
    Matrix path(n, vector<int>(n, -1));

    floyd_shortest_path(graph, path);

    cout << "\npath from 4 to 1: \n";
    print_path(path, 4, 1);


    return 0;
}