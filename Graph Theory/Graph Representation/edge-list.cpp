#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct edge {
    int from, to;
    int cost;

    edge(int from = 0, int to = 0, int cost = 0) : from(from), to(to), cost(cost) {
    }

    void print() {
        cout << "From " << from << " to " << to << " it costs " << cost << '\n';
    }
};
typedef vector<edge> GRAPH;

void add_edge(GRAPH& graph, int from, int to, int cost) { // O(1)
    graph.push_back({from, to, cost});
}

bool compare(edge e1, edge e2) {
    // compare by the cost
    return e1.cost < e2.cost;
}
void print_adj_list_ordered(GRAPH& graph) {
    sort(graph.begin(), graph.end(), compare); // O(E logE)
    for (edge& e : graph) {
        e.print();
    }
}
void test() {
    int nodes;
    cin >> nodes;
    GRAPH graph;

    for (int from = 0; from < nodes; ++from) {
        int neighbors; cin >> neighbors;
        for (int edge = 0; edge < neighbors; ++edge) {
            int to, cost;
            cin >> to >> cost;
            add_edge(graph, from, to, cost);
        }
    }

    print_adj_list_ordered(graph);
}
int main()
{
    test();

    return 0;
}