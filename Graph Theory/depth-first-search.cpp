#include <iostream>
#include <vector>
#include <cassert>
#include <map>

using namespace std;

typedef vector< vector<int> > GRAPH;

void add_edge(GRAPH& graph, int from, int to, bool isDirected = true) {
    assert(from < graph.size());

    graph[from].push_back(to);
    if (!isDirected) {
        assert(to < graph.size());
        graph[to].push_back(from);
    }
}

void dfs(GRAPH& graph, int node, vector<bool>& visited) { // O(N + M) time - O(N) memory
    visited[node] = true;

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) { // to avoid cycling
            cout << "\tWe can reach " << neighbor << '\n';
            dfs(graph, neighbor, visited);
        }
    }
}

/// reachability problem:
void reachability(GRAPH& graph) {
    int nodes = graph.size();
    for (int node = 0; node < nodes; ++node) {
        vector<bool> visited(nodes); // reset for each node
        cout << "Reachable set for node " << node << " is\n";
        dfs(graph, node, visited);
    }
}

/// kill process problem
map<int, vector<int> > build_graph(vector<int>& pid, vector<int>& ppid) {
    int n = pid.size();
    map<int, vector<int> > tree;
    for (int i = 0; i < n; ++i) {
        // from parent to process:
        tree[ppid[i]].push_back(pid[i]);
    }
    
    return tree;
}
void killed_processes(map<int, vector<int> >& graph, int process, vector<int>& killed, map<int, bool>& visited) {
    // dfs function
    
    killed.push_back(process);
    visited[process] = true;
    
    for (int subProcess : graph[process]) {
        if (!visited[subProcess])
            killed_processes(graph, subProcess, killed, visited);
    }
}
vector<int> killProcess(vector<int>& pid /*process id*/, vector<int>& ppid /*parent process id*/, int kill) {
    // build a graph
    map<int, vector<int> > graph = build_graph(pid, ppid);

    vector<int> killed;
    map<int, bool> visited;
    killed_processes(graph, kill, killed, visited);
    return killed;
}


/// https://leetcode.com/problems/employee-importance/
class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};
int getImportance(vector<Employee*> employees, int id) { // O(n^2)
    // we can make a map {id, employee} to make the solution O(n) only

    int total = 0;
    for (Employee* e : employees) {
        if (e->id == id) {
            total += e->importance; // my importance
            for (int subId : e->subordinates)
                total += getImportance(employees, subId); // add all my subordinates

        }
    }
    return total;
}


/// Connected Components problem
void consume_component(GRAPH& graph, int node, vector<bool>& visited) {
    visited[node] = true;
    for (int neighbor : graph[node])
        if (!visited[neighbor])
            consume_component(graph, neighbor, visited);
}
int count_components(int n, vector< vector<int> /*[from, to]*/ >& edges) { // time & memory = O(E + V)
    // build a standard graph:
    GRAPH graph(n); // O(E + V)
    for (auto& edge : edges)
        add_edge(graph, edge[0], edge[1], false);

    // count:
    int result = 0;
    vector<bool> visited(n);
    for (int node = 0; node < n; ++node) {
        if (!visited[node]) {
            ++result;
            consume_component(graph, node, visited);
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////

void print(vector<int>& vec) {
    for(int i : vec) 
        cout << i << ' ';
    cout << endl;
}
void reachability_test() {
    int nodes;
    cin >> nodes;
    GRAPH graph(nodes);

    for (int from = 0; from < nodes; ++from) {
        int neighbors; cin >> neighbors;
        while (neighbors--) {
            int to; cin >> to;
            add_edge(graph, from, to);
        }
    }

    reachability(graph);
}
void kill_process_test() {
    vector<int> pid = {13, 7, 24, 43, 17, 8};
    vector<int> ppid = {7, 0, 7, 13, 13, 17};
    int kill = 7;
    
    cout << "killed processes are: ";
    vector<int> killed = killProcess(pid, ppid, kill);
    print(killed);
}
void count_component_test() {
    int n, e; cin >> n >> e;
    vector< vector<int> > edges;
    for (int i = 1; i <= e; ++i) {
        int from, to;
        cin >> from >> to;
        edges.push_back({from, to});
    }

    cout << count_components(n, edges) << endl;
}

int main()
{
    //reachability_test();

    //kill_process_test();

    count_component_test();

    return 0;
}