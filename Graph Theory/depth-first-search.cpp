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


/////////////////// DFS on a Matrix //////////////////////////
// you should notice that the graph can be exist implicitly..
// one of the examples is the Matrix

// direction arrays:
int dr4[4] = {-1, 1, 0, 0}; // delta for: up, down, left, right
int dc4[4] = {0, 0, -1, 1};

bool is_valid(int r, int c, int n, int m) {
    return (r >= 0 and r < n) and (c >= 0 and c < m);
}

/// https://leetcode.com/problems/flood-fill/
void update_image(vector<vector<int>>& image, int sr, int sc, int oldColor, int newColor, vector< vector<bool> >& visited) {
    const int n = image.size(), m = image[0].size();
    if (!is_valid(sr, sc, n, m) or visited[sr][sc] or image[sr][sc] != oldColor)
        return;

    image[sr][sc] = newColor;
    visited[sr][sc] = true;

    // flood fill: the trivial way:
    /*update_image(image, sr - 1, sc, oldColor, newColor, visited);
    update_image(image, sr + 1, sc, oldColor, newColor, visited);
    update_image(image, sr, sc - 1, oldColor, newColor, visited);
    update_image(image, sr, sc + 1, oldColor, newColor, visited);*/

    // we can use direction arrays:
    for (int d = 0; d < 4; ++d) // iterate over all possible positions
        update_image(image, sr + dr4[d], sc + dc4[d], oldColor, newColor, visited);
    /// competitive programming tip: randomizing the direction calls will end up with a faster performance

    // another way (especially for 24 neighbors case) : using 2 for loops (from -2 to 2)
}
vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
    /** time complexity:
     * let N = R*C
     * then E = 4N
     * O(N + E) = O(N)
     *
     * memory complexity = O(N)
     */

    const int n = image.size(), m = image[0].size();
    vector< vector<bool> > visited(n, vector<bool>(m));
    int oldColor = image[sr][sc];
    update_image(image, sr, sc, oldColor, color, visited);
    return image;
}

/// https://leetcode.com/problems/count-sub-islands/
bool is_sub_island(vector<vector<int>>& grid1, vector<vector<int>>& grid2, int r, int c, const int n, const int m,
                   vector< vector<bool> >& visited) {
    // validate:
    if (!is_valid(r, c, n, m) or visited[r][c] or !grid2[r][c])
        return true;

    visited[r][c] = true; // we can also use the same grid to mark the visited cells
    bool isSub = grid1[r][c];
    for (int i = 0; i < 4; ++i) {
        isSub &= is_sub_island(grid1, grid2, r + dr4[i], c + dc4[i], n, m, visited);
    }

    return isSub;
}
int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
    const int n = grid1.size(), m = grid1[0].size();
    vector< vector<bool> > visited(n, vector<bool>(m));

    int result = 0;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (grid2[r][c] and !visited[r][c])
                result += is_sub_island(grid1, grid2, r, c, n, m, visited);
        }
    }

    // we can alternatively use a bool variable as a class attribute
    // instead of returning bool from dfs function

    return result;
}

/// https://leetcode.com/problems/coloring-a-border/
void dfs(vector<vector<int>>& grid, vector<vector<int>>& newGrid, int r, int c,
        const int n, const int m, int oldColor, int color, vector< vector<bool> >& visited) {

    if (!is_valid(r, c, n, m) or visited[r][c] or grid[r][c] != oldColor)
        return;

    visited[r][c] = true;
    bool isBorder = false;
    for (int i = 0; i < 4; ++i) {
        int adjr = r + dr4[i], adjc = c + dc4[i];
        isBorder |= (!is_valid(adjr, adjc, n, m) or grid[adjr][adjc] != oldColor);

        dfs(grid, newGrid, adjr, adjc, n, m, oldColor, color, visited);
    }

    if (isBorder)
        newGrid[r][c] = color;
}
vector<vector<int>> colorBorder(vector<vector<int>>& grid, int row, int col, int color) {
    const int n = grid.size(), m = grid[0].size();
    int oldColor = grid[row][col];
    vector< vector<bool> > visited(n, vector<bool>(m));

    auto newGrid = grid;
    dfs(grid, newGrid, row, col, n, m, oldColor, color, visited);
    return newGrid;
}


/// https://leetcode.com/problems/number-of-closed-islands/
bool isClosed;
void dfs(vector<vector<int>>& grid, int r, int c, const int n, const int m, vector< vector<bool> >& visited) {
    // validate:
    if (!is_valid(r, c, n, m) or grid[r][c] != 0 or visited[r][c])
        return;

    visited[r][c] = true;

    for (int i = 0; i < 4; ++i) {
        int adjr = r + dr4[i], adjc = c + dc4[i];

        // there are 2 possible surroundings {1, boundary}
        // so if the second case happen => not closed
        // otherwise => closed
        isClosed &= is_valid(adjr, adjc, n, m);
        dfs(grid, adjr, adjc, n, m, visited);
    }
}
int closedIsland(vector<vector<int>>& grid) {
    const int n = grid.size(), m = grid[0].size();

    // we also can use CCid matrix to do the same job of "visited" matrix
    vector< vector<bool> > visited(n, vector<bool>(m));

    int result = 0;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (grid[r][c] == 0 and !visited[r][c]) { // new CC
                isClosed = true;
                dfs(grid, r, c, n, m, visited);
                result += isClosed;
            }
        }
    }

    return result;
}


/// https://leetcode.com/problems/detect-cycles-in-2d-grid/
bool isThereCycle = false;
void dfs(vector<vector<char>>& grid, int r, int c, int n, int m, char val, vector<vector<bool>>& visited, int par_r = -1, int par_c = -1) {
    // validate:
    if (!is_valid(r, c, n, m) or grid[r][c] != val or isThereCycle) // invalid, not-CC
        return;

    if (visited[r][c]) { // a cycle
        isThereCycle = true;
        return;
    }

    visited[r][c] = true;

    for (int i = 0; i < 4; ++i) {
        int nr = r + dr4[i];
        int nc = c + dc4[i];
        if (nr == par_r and nc == par_c) // fake cycle from undirected edge
            continue;

        dfs(grid, nr, nc, n, m, val, visited, r, c);
    }
}
bool containsCycle(vector<vector<char>>& grid) {
    const int n = grid.size(), m = grid[0].size();
    vector<vector<bool>> visited(n, vector<bool>(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!visited[i][j]) { // new CC
                char val = grid[i][j];
                dfs(grid, i, j, n, m, val, visited);
                if (isThereCycle)
                    return true;
            }
        }
    }
    return isThereCycle;
}


//////////////// Reductions on Graph //////////////////
/// https://leetcode.com/problems/restore-the-array-from-adjacent-pairs/
vector<int> ans;
void dfs(int node, unordered_map<int, vector<int>>& graph, unordered_map<int, bool>& visited) {
        ans.push_back(node);
        visited[node] = true;
        for (int neighbor : graph[node])
            if (!visited[neighbor])
                dfs(neighbor, graph, visited);
}
vector<int> restoreArray(vector<vector<int>>& adjacentPairs) {
    unordered_map<int, vector<int>> graph;
    for (auto pair : adjacentPairs) {
        // undirected edge:
        graph[pair[0]].push_back(pair[1]);
        graph[pair[1]].push_back(pair[0]);
    }

    // obtain root:
    int root;
    for (auto node : graph) {
        if (node.second.size() == 1) {
            root = node.first;
            break;
        }
    }

    unordered_map<int, bool> visited;
    dfs(root, graph, visited);

    return ans;
}

/// https://leetcode.com/problems/smallest-string-with-swaps
typedef vector< vector<int> > GRAPH;
void add_edge(GRAPH& graph, int from, int to) {
        // undirected
        graph[from].push_back(to);
        graph[to].push_back(from);
}
void dfs(int node, GRAPH& graph, vector<bool>& visited, string& s, string& ccChars, vector<int>& ccIdx) {
    ccChars.push_back(s[node]);
    ccIdx.push_back(node);

    visited[node] = true;

    for(int neighbor : graph[node])
        if (!visited[neighbor])
            dfs(neighbor, graph, visited, s, ccChars, ccIdx);
}
string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) { // O(n logn)
    int n = s.size();

    // build graph
    GRAPH graph(n);
    for (auto pair : pairs) {
        add_edge(graph, pair[0], pair[1]);
    }

    vector<bool> visited(n);
    for (int node = 0; node < n; ++node) {
        if (!graph[node].empty() and !visited[node]) { // new CC
            string ccChars;
            vector<int> ccIdx;
            dfs(node, graph, visited, s, ccChars, ccIdx);

            sort(ccChars.begin(), ccChars.end());
            sort(ccIdx.begin(), ccIdx.end());
            int ccLen = ccChars.size();
            for (int i = 0; i < ccLen; ++i) {
                s[ccIdx[i]] = ccChars[i];
            }
        }
    }

    return s;
}


/// https://leetcode.com/problems/longest-consecutive-sequence
void add_edge(unordered_map<int, vector<int> >& graph, int from, int to) {
        graph[from].push_back(to);
        graph[to].push_back(from);
}
int dfs(int node, unordered_map<int, vector<int> >& graph, unordered_map<int, bool>& visited) {
    visited[node] = true;

    int len = 1;
    for (int neighbor : graph[node])
        if (!visited[neighbor])
            len += dfs(neighbor, graph, visited);
    return len;
}
int longestConsecutive(vector<int>& nums) {
    unordered_map<int, vector<int> > graph;
    vector<int> dummy;
    for (int node : nums) {
        if (graph.count(node))
            continue;

        graph.insert({node, dummy});
        if (graph.count(node - 1))
            add_edge(graph, node, node - 1);
        if (graph.count(node + 1))
            add_edge(graph, node, node + 1);
    }

    int ans = 0;
    unordered_map<int, bool> visited;
    for (auto item : graph) {
        if (!visited[item.first])
            ans = max(ans, dfs(item.first, graph, visited));
    }

    return ans;
}


///////// Detect cycles in directed graph ///////////
/* here there are 4 cases for edges:
* tree edge
* forward edge
* back edge => Cycle source
* cross edge
*/

void edge_classify(int node, GRAPH& graph, vector<int>& started, vector<int>& finished, int& time) {
    started[node] = time; ++time;

    for (int neighbor : graph[node]) {
        if (started[neighbor] == -1) {
            cout << node << " -> " << neighbor << " Tree Edge\n";
            edge_classify(neighbor, graph, started, finished, time);
        }
        else {
            if (started[node] < started[neighbor])
                cout << node << " -> " << neighbor << " Forward Edge\n";
            else if (finished[neighbor] == -1)
                cout << node << " -> " << neighbor << " Back Edge\n"; // cycle: started before me, didn't finish yet
            else
                cout << node << " -> " << neighbor << " Cross Edge\n";
        }
    }

    finished[node] = time; ++time;
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
void flood_fill_test() {
    vector< vector<int> > image = {{ 1, 1, 1 },
                                   { 1, 1, 0 },
                                   { 1, 0, 1 }};

    vector< vector<int> > image1 = {{0, 0, 0},
                                    {0, 0, 0}};

    image = floodFill(image, 1, 1, 2);
    for (auto row : image)
        print(row);
}

void test() {
    vector< vector<char> > grid = { {'a', 'a'},
                                   {'a', 'x'} };
    cout << containsCycle(grid) << endl;
}

int main()
{
    //reachability_test();

    //kill_process_test();

    //count_component_test();

    //flood_fill_test();

    test();

    return 0;
}
