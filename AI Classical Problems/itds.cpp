#include <bits/stdc++.h>
using namespace std;

class Graph {
    int V; // vertices
    list<int> *adj;

    bool DLS(int src, int target, int limit); // depth limit search

public:
    Graph(int v);

    void add_edge(int src, int des);

    bool IDDFS(int src, int target, int max_depth);
};

Graph::Graph(int v) {
    this->V = v;
    adj = new list<int>[V];
}

void Graph::add_edge(int src, int des) {
    adj[src].push_back(des); // directed edge
}

bool Graph::DLS(int src, int target, int limit) {
    if (src == target) {
        cout << "Path: " << target << ' '; // start printing recursively
        return true;
    }

    if (limit == 0) // reach the limit => can't go more!
        return false;

    for (int neighbor : adj[src]) {
        if (DLS(neighbor, target, limit - 1)) {
            cout << src << ' ';
            return true;
        }
    }

    return false; // goal not found or need to go deeper
}

bool Graph::IDDFS(int src, int target, int max_depth) {
    for (int limit = 0; limit <= max_depth; ++limit) {
        if (DLS(src, target, limit))
            return true;
    }

    return false;
}

int main() {
    Graph g(6);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);
    g.add_edge(1, 4);
    g.add_edge(2, 5);
    g.add_edge(2, 6);

    int src, target, max_depth;
    cout << "Enter the source and the target: \n";
    cin >> src >> target;

    cout << "Enter the max depth: \n";
    cin >> max_depth;

    if (g.IDDFS(src, target, max_depth))
        cout << "\nCan reach within the max depth\n";
    else
        cout << "\nCan't reach within the max depth\n";

    return 0;
}