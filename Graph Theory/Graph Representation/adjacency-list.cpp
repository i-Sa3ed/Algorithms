#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// adj matrix is not good for sparse graph
// here the adj list come to save the memory for us !

// to handle weighted graph case
struct edge {
    int to;
    int cost = 0;

    void print() {
        cout << " (" << to << ", " << cost << ") ";
    }
};

typedef vector< vector<edge> > GRAPH;
/// utility:
void assert_indices(GRAPH& graph, int from, int to) {
    // test the indices
    assert(from < graph.size() and to < graph.size());
}

void add_edge(GRAPH& graph, int from, int to, int cost, bool isDirected = true) {
    assert_indices(graph, from, to);

    graph[from].push_back({to, cost});
    if (!isDirected)
        graph[to].push_back({from, cost});
}

////////////////////////////////////////////////////////////

void print_adj_list(GRAPH& graph) {
    int n = graph.size();
    for (int from = 0; from < n; ++from) {
        cout << from << " => ";
        int neighbors = graph[from].size();
        for (int edge = 0; edge < neighbors; ++edge) {
            graph[from][edge].print();
        }
        cout << '\n';
    }
}
void test() {
    int nodes, edges;
    cin >> nodes >> edges;
    GRAPH graph(nodes);

    for (int from = 0; from < nodes; ++from) {
        // take all neighbors:
        int neighbors; cin >> neighbors;
        for (int i = 0; i < neighbors; ++i) {
            int to, cost; cin >> to >> cost;
            add_edge(graph, from, to, cost);
        }
    }

    print_adj_list(graph);
}
int main()
{
    test();
    return 0;
}