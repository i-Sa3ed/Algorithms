#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

typedef vector< vector<int> > GRAPH; // for simplicity

/// utility:
void assert_indices(GRAPH& graph, int from, int to) {
    // test the indices
    assert(from < graph.size() and to < graph.size());
    assert(to < graph[from].size() and from < graph[to].size());
}

void add_directed_edge(GRAPH& graph, int from, int to) {
    // directed: from => to
    assert_indices(graph, from, to);

    graph[from][to] += 1; // add one edge
}
void add_undirected_edge(GRAPH& graph, int from, int to) {
    // undirected: from <=> to
    assert_indices(graph, from, to);

    graph[from][to] += 1;
    graph[to][from] += 1;
}

/// weighted edges:
// here we assume that there is no multiple edges
void add_directed_edge(GRAPH& graph, int from, int to, int weight) {
    assert_indices(graph, from, to);

    graph[from][to] = weight;
}
void add_undirected_edge(GRAPH& graph, int from, int to, int weight) {
    assert_indices(graph, from, to);

    graph[from][to] = weight;
    graph[to][from] = weight;
}

/////////////////////////////////////////////////////////////////////

typedef vector< vector< vector<int> > > MultipleEdgesGRAPH;

void assert_indices(MultipleEdgesGRAPH& graph, int from, int to) {
    // test the indices
    assert(from < graph.size() and to < graph.size());
    assert(to < graph[from].size() and from < graph[to].size());
}
void add_edge(MultipleEdgesGRAPH& graph, int from, int to, int weight, bool isDirected = true) {
    assert_indices(graph, from, to);

    graph[from][to].push_back(weight);
    if (!isDirected)
        graph[to][from].push_back(weight);
}

///////////////////// test & main ///////////////////////

void print_adjacency_matrix(GRAPH& graph) {
    int nodes = graph.size();
    for (int from = 0; from < nodes; ++from) {
        for (int to = 0; to < nodes; ++to) {
            if (graph[from][to] > 0)
                cout << "From " << from << " to " << to << " there are " << graph[from][to] << " edges\n";
        }
    }
}
void print_adjacency_matrix(MultipleEdgesGRAPH& graph) {
    int nodes = graph.size();
    for (int from = 0; from < nodes; ++from) {
        for (int to = 0; to < nodes; ++to) {
            if (graph[from][to].size() > 0) {
                cout << "From " << from << " to " << to << " the possible costs are: ";
                for (int cost : graph[from][to])
                    cout << cost << ' ';
                cout << '\n';
            }
        }
    }
}

void test_adjacency_matrix() {
    // let's build a graph
    int nodes, edges;
    cin >> nodes >> edges;
    GRAPH graph(nodes, vector<int>(nodes));

    for (int i = 1; i <= edges; ++i) {
        int from, to;
        cin >> from >> to;
        add_directed_edge(graph, from, to);
    }

    print_adjacency_matrix(graph);
}

void test_adjacency_matrix_multiple_edges() {
    int nodes, edges;
    cin >> nodes >> edges;

    MultipleEdgesGRAPH graph(nodes, vector< vector<int> >(nodes));
    // O(V^2 + E) space complexity
    
    for (int e = 1; e <= edges; ++e) {
        int from, to, weight;
        cin >> from >> to >> weight;
        add_edge(graph, from, to, weight);
    }

    print_adjacency_matrix(graph);

}

int main() {
    //test_adjacency_matrix();

    test_adjacency_matrix_multiple_edges();
    return 0;
}