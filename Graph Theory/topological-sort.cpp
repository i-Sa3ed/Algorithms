#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef vector< vector<int> > AdjList; // adjacency list
struct cell {
    int r = 0,
        c = 0;
};

// Delta for: up, right, down, left
int dr[4] { -1, 0, 1, 0 };
int dc[4] { 0, 1, 0, -1 };

bool is_valid(int r, int c, int n, int m) {
    return (r >= 0 and r < n) and (c >= 0 and c < m);
}

void add_edge(AdjList& graph, int from, int to, bool isUndir = false){
    graph[from].push_back(to);
    if (isUndir)
        graph[to].push_back(from);
}
void build_graph(AdjList& graph, vector<vector<int>>& edgeList, bool isReversed = true) {
    for (auto edge : edgeList) {
        if (isReversed)
            graph[edge[1]].push_back(edge[0]);
        else
            graph[edge[0]].push_back(edge[1]);
    }
}
vector<int> compute_indegree(AdjList& graph, bool isOneBased = false) {
    int n = graph.size();
    vector<int> indegree(n);

    for (int node = 0 + isOneBased; node < n; ++node) {
        for (int dependant : graph[node])
            ++indegree[dependant];
    }

    return indegree;
}

/// Implementation ///

/// https://leetcode.com/problems/course-schedule/
vector<int> top_sort(AdjList& graph, bool isOneBased = false) {
    /** complexity
     * time: O(e+v)
     * memory: O(n)
     */

    const int n = graph.size();
    vector<int> indegree = compute_indegree(graph);

    queue<int> ready;
    // initiate with 0-indegree nodes:
    for (int node = 0; node < n; ++node) {
        if (indegree[node] == 0)
            ready.push(node);
    }

    vector<int> result;
    while (!ready.empty()) {
        int cur = ready.front();
        ready.pop();
        result.push_back(cur);

        for (int dependant : graph[cur]) {
            --indegree[dependant]; // remove edge
            if (indegree[dependant] == 0) // ready?
                ready.push(dependant); // add it
        }
    }

    if (result.size() < n) // there is some non-processed nodes => cycle
        result.clear();
    return result;
}
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    AdjList graph(numCourses);
    build_graph(graph, prerequisites);

    vector<int> order = top_sort(graph);

    if (order.size() == 0) // cycle
        return false;
    return true;
}


/// Easy Challenges ///

/// Challenge: smallest lexicographical order
// same idea, but use priority_queue instead of queue
// to maintain the ready nodes in a sorted way
vector<int> top_sort_lexi_smallest(AdjList& graph) {
    /** complexity
     * time: O((e+v)*Log(v))
     * memory: O(n)
     */

    const int n = graph.size();
    vector<int> indegree = compute_indegree(graph);

    priority_queue<int, vector<int>, greater<>> ready;
    // initiate with 0-indegree courses:
    for (int node = 0; node < n; ++node) {
        if (indegree[node] == 0)
            ready.push(node);
    }

    vector<int> result;
    while (!ready.empty()) {
        int cur = ready.top();
        ready.pop();
        result.push_back(cur);

        for (int dependant : graph[cur]) {
            --indegree[dependant]; // remove edge
            if (indegree[dependant] == 0) // ready?
                ready.push(dependant); // add it
        }
    }

    if (result.size() < n) // there is some non-processed nodes => cycle
        result.clear();
    return result;
}

/// https://leetcode.com/problems/parallel-courses/
// submitted here:
/// https://www.codingninjas.com/codestudio/problems/parallel-courses_1376444?leftPanelTab=1
int top_sort(AdjList& graph, int& levels) {
    /** complexity
     * time: O(e+v)
     * memory: O(n)
     */

    const int n = graph.size() - 1;
    vector<int> indegree = compute_indegree(graph);

    queue<int> ready;
    // initiate with 0-indegree courses:
    for (int node = 1; node <= n; ++node) {
        if (indegree[node] == 0)
            ready.push(node);
    }

    vector<int> result;
    levels = 1;
    for (int siz = ready.size(); !ready.empty(); ++levels, siz = ready.size()) {
        while (siz--) {
            int cur = ready.front();
            ready.pop();
            result.push_back(cur);

            for (int dependant: graph[cur]) {
                --indegree[dependant]; // remove edge
                if (indegree[dependant] == 0) // ready?
                    ready.push(dependant); // add it
            }
        }
    }
    --levels;

    if (result.size() < n)
        levels = -1; // can't complete the courses
    return levels;
}
int minimum_semesters(int n, vector< vector<int>>& relations) {
    // relation[i] = {prevCourse, nextCourse}

    AdjList graph(n + 1); // 1-based
    build_graph(graph, relations, false);

    // do the normal top sort, but count the # levels processed

    int ans;
    top_sort(graph, ans);
    return ans;
}

/// https://leetcode.com/problems/sequence-reconstruction/
// submit on:
/// https://www.codingninjas.com/codestudio/problems/shortest-common-supersequence_1377949
vector<int> is_unique(AdjList& graph, bool isOneBased = false) {
    int n = graph.size();
    vector<int> indegree = compute_indegree(graph, true);

    queue<int> ready;
    // initiate with 0-indegree courses:
    for (int node = 0 + isOneBased; node < n; ++node) {
        if (indegree[node] == 0)
            ready.push(node);
    }

    vector<int> result;
    while (!ready.empty()) {
        if (ready.size() > 1) // is there multiple-possible choices? => not unique
            break;

        int cur = ready.front();
        ready.pop();
        result.push_back(cur);

        for (int dependant : graph[cur]) {
            --indegree[dependant]; // remove edge
            if (indegree[dependant] == 0) // ready?
                ready.push(dependant); // add it
        }
    }

    if (result.size() < (n - 1)) // there is some non-processed nodes => cycle
        result.clear();
    return result;
}
bool shortestSuperSeq(vector<int> &primary, vector<vector<int>> &secondary, int N, int X, int Y)
{
    int count = 0;
    vector<bool> seen(N + 5);
    
    // create DAG from 'secondary'
    AdjList graph(N + 1);
    for (int i = 0; i < X; ++i) {
        for (int j = 0; j < Y - 1; ++j) {
            int from = secondary[i][j];
            int to = secondary[i][j + 1];
            graph[from].push_back(to); // add edge

            if (!seen[from])
                ++count, seen[from] = true;
            if (!seen[to])
                ++count, seen[to] = true;
        }
    }

    // test for shortest:
    if (count < N)
        return false;

    // test for uniqueness, using top sort:
    vector<int> temp = is_unique(graph, true);
    return (temp == primary);
}

/// https://leetcode.com/problems/minimum-height-trees/
vector<int> min_height_trees(AdjList& graph, bool isOneBased = false) {
    /** complexity
     * time: O(e+v)
     * memory: O(n)
     */

    const int n = graph.size();
    vector<int> indegree = compute_indegree(graph);
    // debug: indegree

    queue<int> ready;
    // initiate with 1-indegree nodes:
    for (int node = 0; node < n; ++node) {
        if (indegree[node] == 1)
            ready.push(node);
    }

    vector<int> result;
    int level = 1;
    for (int siz = ready.size(); !ready.empty(); ++level, siz = ready.size()) {
        result = vector<int>(); // keep only the last level;

        while (siz--) {
            int cur = ready.front();
            ready.pop();
            result.push_back(cur);

            for (int dependant: graph[cur]) {
                --indegree[dependant]; // remove edge
                if (indegree[dependant] == 1) // ready?
                    ready.push(dependant); // add it
            }
        }
    }

    return result;
}
vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
    vector<int> mht;

    // special cases:
    if (n <= 2) {
        for (int i = 0; i < n; ++i) {
            mht.push_back(i);
        }
        return mht;
    }

    // build graph
    AdjList graph(n);
    for (auto edge : edges) {
        add_edge(graph, edge[0], edge[1], true);
    }

    mht = min_height_trees(graph);
    return mht;
}

/// https://leetcode.com/problems/longest-increasing-path-in-a-matrix/
int longestIncreasingPath(vector<vector<int>>& matrix) {
    const int n = matrix.size(), m = matrix[0].size();

    vector< vector<int> > indegree(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            // iterate on neighbors:
            for (int d = 0; d < 4; ++d) {
                int nr = i + dr[d],
                    nc = j + dc[d];
                if (is_valid(nr, nc, n, m) and matrix[nr][nc] < matrix[i][j])
                    ++indegree[i][j];
            }
        }
    }

    queue<cell> ready;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (indegree[i][j] == 0)
                ready.push({i, j});
        }
    }

    int level = 1;
    for (int siz = ready.size(); !ready.empty(); ++level, siz = ready.size()) {
        while (siz--) {
            cell cur = ready.front();
            ready.pop();

            for (int d = 0; d < 4; ++d) {
                int nr = cur.r + dr[d],
                        nc = cur.c + dc[d];
                if (!is_valid(nr, nc, n, m) or matrix[nr][nc] <= matrix[cur.r][cur.c])
                    continue;

                --indegree[nr][nc]; // remove edge
                if (indegree[nr][nc] == 0)
                    ready.push({nr, nc});
            }
        }
    }
    --level;

    return level;
}

/// Top Sort with DFS ///
// more shorter than Kna's algo
// but it's less intuitive :)

/// https://leetcode.com/problems/course-schedule-ii/
bool isCycle = false; // better to make 'dfs' function return bool variable
void dfs_top_sort(int node, AdjList& graph, vector<int>& start, vector<int>& finish, int& time, vector<int>& result) {
    if (isCycle)
        return;

    start[node] = time++; // mark visited

    for (int neighbor : graph[node]) {
        if (start[neighbor] == -1)
            dfs_top_sort(neighbor, graph, start, finish, time, result);
        else if (start[neighbor] < start[node] and finish[neighbor] == -1) { // back edge => cycle
            isCycle = true;
            return;
        }
    }

    result.push_back(node); /// here

    finish[node] = time++;
}
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    AdjList graph(numCourses);
    build_graph(graph, prerequisites);

    vector<int> start(numCourses, -1), finish(numCourses, -1), result;
    int time = 0;
    for (int node = 0; node < numCourses and !isCycle; ++node) {
        if (start[node] == -1)
            dfs_top_sort(node, graph, start, finish, time, result);
    }

    if (isCycle or result.size() < numCourses)
        result.clear();
    reverse(result.begin(), result.end());
    return result;
}

/////////////////////////////////////////////////////////////
/// test and main
void print(vector<int>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << ' ';
    }
    cout << endl;
}

void lexi_order_test() {
    int n, e;
    cin >> n >> e;
    vector< vector<int> > edges;
    for (int edge = 0; edge < e; ++edge) {
        int from, to;
        cin >> from >> to;
        edges.push_back({to, from}); // prerequisits order
    }

    AdjList graph(n);
    build_graph(graph, edges);

    vector<int> order = top_sort_lexi_smallest(graph);
    print(order);
}
void min_semesters_test() {
    int n, e;
    cin >> n >> e;
    vector< vector<int> > edges;
    for (int edge = 0; edge < e; ++edge) {
        int from, to;
        cin >> from >> to;
        edges.push_back({from, to});
    }

    cout << minimum_semesters(n, edges) << endl;
}
void sequence_test() {
    int t; cin >> t;
    while (t--) {
        int n, x, y;
        cin >> n >> x >> y;
        vector<int> primary(n);
        for (int i = 0; i < n; ++i) {
            cin >> primary[i];
        }
        vector< vector<int> > secondary(x, vector<int>(y));
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < y; ++j) {
                cin >> secondary[i][j];
            }
        }

        cout << shortestSuperSeq(primary, secondary, n, x, y) << endl;
    }
}
void min_height_tree_test() {
    int n, e;
    cin >> n >> e;
    vector< vector<int> > edges;
    for (int i = 0; i < e; ++i) {
        int from, to;
        cin >> from >> to;
        edges.push_back({from, to});
    }

    vector<int> res = findMinHeightTrees(n, edges);
    print(res);
}
void longest_path_test() {
    int n, m;
    cin >> n >> m;
    vector< vector<int> > matrix(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> matrix[i][j];
        }
    }

    cout << longestIncreasingPath(matrix) << endl;
}
void courses_test() {
    int n, e; cin >> n >> e;
    vector<vector<int>> edges(e);
    for (int i = 0; i < e; ++i) {
        int from, to;
        cin >> from >> to;
        edges.push_back({from, to});
    }

    vector<int> res = findOrder(n, edges);
    print(res);
}

int main() {
    //lexi_order_test();

    //min_semesters_test();

    //sequence_test();

    //min_height_tree_test();

    //longest_path_test();

    courses_test();

    return 0;
}