#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector< vector<int> > GRAPH;
// Delta for: up, right, down, left
int dr[4] { -1, 0, 1, 0 };
int dc[4] { 0, 1, 0, -1 };

/// utilities
void print(vector<int>& vec) {
    for(int i = vec.size() - 1; i >= 0; --i)
        cout << vec[i] << ' ';
    cout << endl;
}

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

bool is_valid(pair<int, int> loc, int n, int m) {
    return (loc.first >= 0 and loc.first < n) and (loc.second >= 0 and loc.second < m);
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
    const int n = graph.size(), m = graph[0].size();
    queue<int> breadth;
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
 * Tree:
 * 1- edges = nodes - 1
 * 2- no cycles
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

/// https://leetcode.com/problems/shortest-path-to-get-food/
pair<int, int> obtain_person_loc(vector< vector<char> >& matrix) {
    const int n = matrix.size(), m = matrix[0].size();

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (matrix[r][c] == '*')
                return {r, c};
        }
    }

    pair<int, int> dummy;
    return dummy;
}
int shortest_path(vector< vector<char> >& matrix, pair<int, int> loc) {
    const int n = matrix.size(), m = matrix[0].size();

    vector< vector<bool> > added(n, vector<bool>(m));
    queue<pair<int, int>> breadth;
    breadth.push(loc);
    added[loc.first][loc.second] = true;

    for(int level = 0, siz = breadth.size(); !breadth.empty(); ++level, siz = breadth.size()) {
        while (siz--) {
            pair<int, int> cur = breadth.front();
            breadth.pop();

            // add neighbors:
            for (int d = 0; d < 4; ++d) {
                pair<int, int> adj = {cur.first + dr[d], cur.second + dc[d]};
                if (is_valid(adj, n, m) and matrix[adj.first][adj.second] != 'X' and !added[adj.first][adj.second]) {
                    if (matrix[adj.first][adj.second] == '#')
                        return level + 1;

                    breadth.push(adj);
                    added[adj.first][adj.second] = true;
                }
            }
        }
    }

    return -1; // can't reach any food

    /// Dr. Mostafa tip
    // Tip: we can use the matrix itself to mark visited by setting matrix[nr][nc] = 'X';
    // This is good for competitions, but not industry / interviews
}
int getFood(vector< vector<char> >& matrix) {
    const int n = matrix.size(), m = matrix[0].size();

    // obtain the root (person location)
    pair<int, int> loc = obtain_person_loc(matrix);

    // search for shortest path to the food (#)
    // bfs function

    return shortest_path(matrix, loc);
}

/// https://leetcode.com/problems/jump-game-iii/
bool canReach(vector<int>& arr, int start) {
    const int n = arr.size();
    queue<int> breadth;
    vector<bool> added(n);

    breadth.push(start);
    added[start] = true;

    for (int level = 0, siz = 1; !breadth.empty(); ++level, siz = breadth.size()) {
        while (siz--) { // process only the current level
            int cur = breadth.front();
            breadth.pop();

            // safer than associating it with neighbors
            if (arr[cur] == 0)
                return true;

            int neighbors[] = {cur + arr[cur], cur - arr[cur]};

            for (int neighbor : neighbors) {
                if ((neighbor >= 0 and neighbor < n) and !added[neighbor]) {
                    breadth.push(neighbor);
                    added[neighbor] = true;
                }
            }
        }
    }

    return false;
}

/// https://leetcode.com/problems/minimum-operations-to-convert-number/
int minimumOperations(vector<int>& nums, int start, int goal) {
    // O(N * M)
    // M = 1001 (possible states)
    const int n = nums.size();
    queue<int> X;
    vector<bool> added(1005);

    X.push(start);
    added[start] = true;

    for (int level = 0, siz = 1; !X.empty(); ++level, siz = X.size()) {
        while (siz--) { // process only the current level
            int x = X.front();
            X.pop();

            for (int i = 0; i < n; ++i) {
                int neighbors[] = {x + nums[i], x - nums[i], x ^ nums[i]};
                
                for (int neighbor : neighbors) {
                    if (neighbor == goal)
                        return level + 1;

                    if ((neighbor >= 0 and neighbor <= 1000) and !added[neighbor]) {
                        X.push(neighbor);
                        added[neighbor] = true;
                    }
                }
            }
        }
    }

    return -1;
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

    //valid_tree_test();

    return 0;
}