#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>

using namespace std;

typedef vector< unordered_set<int> > GRAPH;

void add_edge(GRAPH& graph, int from, int to, bool isDirected = true) {
    assert(from < graph.size());

    graph[from].insert(to); // O(hashing)
    if (!isDirected) {
        assert(to < graph.size());
        graph[to].insert(from);
    }
}

void print_adj_hashset(GRAPH& graph) {
    int n = graph.size();
    for (int from = 0; from < n; ++from) {
        cout << from << " has neighbors: ";
        int neighbors = graph[from].size();
        auto it = graph[from].begin();
        for (int to = 0; to < neighbors; ++to, ++it) {
            cout << *it << ' ';
        }
        cout << '\n';
    }
}

void test() {
    int nodes, edges;
    cin >> nodes >> edges;
    GRAPH graph(nodes);

    for (int e = 1; e <= edges; ++e) {
        int from, to;
        cin >> from >> to;
        add_edge(graph, from, to);
    }

    print_adj_hashset(graph);
}
int main()
{
    test();

    return 0;
}

/*
 * Disadvantages
	- No order guarantee for edges
	- Impractical for multiple edges  (we may do workarounds)
	- Hash tables extra memory
	- Like any hash tables, more caution to properly deal with the load (load factor)
 */