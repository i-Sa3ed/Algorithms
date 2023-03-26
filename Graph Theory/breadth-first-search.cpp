#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// utility
void print(vector<int>& vec) {
    for(int i = vec.size() - 1; i >= 0; --i)
        cout << vec[i] << ' ';
    cout << endl;
}

typedef vector< vector<int> > GRAPH;
void add_edge(GRAPH& graph, int from, vector<int>& To, bool isUndir = true) {
    for (int to : To) {
        graph[from].push_back(to);
        if (isUndir)
            graph[to].push_back(from);
    }
}
void add_edge(GRAPH& graph, int from, int to, bool isUndir = true) {
    graph[from].push_back(to);
    if (isUndir)
        graph[to].push_back(from);
}

/// Implementation
// my trial
void bfs(int start, GRAPH& graph) {
    int n = graph.size();
    queue<int> breadth; breadth.push(start);
    vector<bool> added(n); added[start] = true;

    while (!breadth.empty()) {
        // get the front item:
        int cur = breadth.front();
        breadth.pop();

        // add its neighbors:
        for (int neighbor : graph[cur]) {
            if (!added[neighbor]) {
                cout << "the start " << neighbor << " will be added\n";
                breadth.push(neighbor);
                added[neighbor] = true;
            }
        }
    }
}

// lecture first-version
const int OO = 1e6;
vector<int> /*length of each node*/ bfs1(int start, GRAPH& graph) {
    int n = graph.size();

    // we keep the nodes and its levels in a pair
    queue< pair<int, int> /*<node, len>*/ > breadth;
    vector<int> len(n, OO); // initialize with a big value
    breadth.push( {start, 0} );
    len[start] = 0;

    while (!breadth.empty()) {
        pair<int, int> fr = breadth.front();
        breadth.pop();

        for (int neighbor : graph[fr.first]) {
            if (len[neighbor] == OO) { // not visited yet
                breadth.push({neighbor, fr.second + 1});
                len[neighbor] = fr.second + 1;
            }
        }
    }

    return len;
}

// lecture second-version
// a smarter implementation
    // now we don't need to keep the level of each node (i.e. don't need a pair)
vector<int> bfs2(int start, GRAPH& graph) {
    queue<int> breadth;
    int n = graph.size();
    vector<int> len(n, OO);

    breadth.push(start);
    len[start] = 0;

    for (int level = 0, siz = 1; !breadth.empty(); ++level, siz = breadth.size()) {
        while (siz--) { // process only the current level
            int cur = breadth.front();
            breadth.pop();

            for (int neighbor : graph[cur]) {
                if (len[neighbor] == OO) {
                    breadth.push(neighbor);
                    len[neighbor] = level + 1;
                }
            }
        }
    }

    return len;
}

/** complexity
 * time: O(E + V)
 * memory (i.e. queue) : O(V)
 * Note: similar to DFS
 */

/// Challenge: print path for each node
void get_parents(int start, GRAPH& graph, vector<int>& parent) {
    // bfs function
    queue<int> breadth;
    vector<bool> visited(graph.size());
    breadth.push(start);
    visited[start] = true;

    while (!breadth.empty()) {
        int cur = breadth.front();
        breadth.pop();

        for (int child : graph[cur]) {
            if (!visited[child]) {
                breadth.push(child);
                visited[child] = true;
                parent[child] = cur;
            }
        }
    }
}
void get_path(int node, vector<int>& parent, vector<int>& path) {
    if (node == -1) { // not exist
        path = vector<int>();
        return;
    }

    path.push_back(node);
    if (node == 0) // found it
        return;

    get_path(parent[node], parent, path);
}
void print_paths(int start, GRAPH& graph) {
    // stores the parent of each node in bfs tree
    unsigned int n = graph.size();
    vector<int> parent(n, -1);

    get_parents(start, graph, parent);
    //print(parent);

    // print the paths
    for (int goal = 1; goal < n; ++goal) {
        vector<int> path;
        get_path(goal, parent, path);
        cout << "Path from 0 to " << goal << " is: ";
        if (path.empty())
            cout << "Not Exist\n";
        else
            print(path);
    }
}

/// https://leetcode.com/problems/graph-valid-tree/
/*
 * valid tree can contain multiple CCs
 */

bool cc_cycle(int start, GRAPH& graph, vector<bool>& visited, vector<int>& parent) {
    // bfs function
    queue<int> breadth;
    breadth.push(start);
    visited[start] = true;

    while (!breadth.empty()) {
        int cur = breadth.front();
        breadth.pop();

        for (int neighbor : graph[cur]) {
            if (visited[neighbor]) {
                if (neighbor != parent[cur]) // actual cycle
                    return true;
            }
            else {
                breadth.push(neighbor);
                visited[neighbor] = true;
                parent[neighbor] = cur;
            }
        }
    }

    return false;
}
bool has_cycle(GRAPH& graph) {
    unsigned int n = graph.size();
    vector<int> parent(n, -1); // used to detect fake cycles
    vector<bool> visited(n);
    for (int node = 0; node < n; ++node) {
        if (!visited[node] and cc_cycle(node, graph, visited, parent))
            return true;
    }

    return false;
}
bool valid_tree(int nodes, vector< vector<int> >& edges) {
    if (nodes != edges.size() + 1)
        return false;

    // build the graph
    GRAPH graph(nodes);
    for (auto edge : edges) {
        add_edge(graph, edge[0], edge[1]);
    }

    return !has_cycle(graph);
}

/////////////////////////////////////////

void implementation_test() {
    int n = 9;
    GRAPH graph(n);

    vector<int> to = {3, 5, 6};
    add_edge(graph, 1, to);
    to = {5, 4, 7};
    add_edge(graph, 3, to);
    to = {4};
    add_edge(graph, 5, to);
    to = {0};
    add_edge(graph, 6, to);
    to = {2};
    add_edge(graph, 4, to);
    add_edge(graph, 0, to);
    to = {8};
    add_edge(graph, 2, to);

    //bfs(1, graph);

    vector<int> trav = bfs2(1, graph);
    print(trav);
}
void print_paths_test() {
    int tests; cin >> tests;
    while (tests--) {
        int n, e;
        cin >> n >> e;
        GRAPH graph(n);

        while (e--) {
            int from, to;
            cin >> from >> to;
            add_edge(graph, from, to, false);
        }

        print_paths(0, graph);
        cout << endl;
    }
}
void valid_tree_test() {
    int n, e;
    cin >> n >> e;
    vector< vector<int> > edges;
    while (e--) {
        int from, to;
        cin >> from >> to;
        edges.push_back({from, to});
    }

    cout << valid_tree(n, edges) << endl;
}

int main() {
    //implementation_test();

    //print_paths_test();

    valid_tree_test();

    return 0;
}