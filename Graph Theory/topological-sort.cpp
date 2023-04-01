#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef vector< vector<int> > AdjList; // adjacency list

void build_graph(AdjList& graph, vector<vector<int>>& edgeList, bool isReversed = true) {
    for (auto edge : edgeList) {
        if (isReversed)
            graph[edge[1]].push_back(edge[0]);
        else
            graph[edge[0]].push_back(edge[1]);
    }
}

/// Implementation ///

/// https://leetcode.com/problems/course-schedule/
vector<int> compute_indegree(AdjList& graph) {
    const int n = graph.size();
    vector<int> indegree(n);
    for (int node = 0; node < n; ++node) {
        for (int dependant : graph[node])
            ++indegree[dependant];
    }

    return indegree;
}
vector<int> top_sort(AdjList& graph) {
    /** complexity
     * time: O(e+v)
     * memory: O(n)
     */

    const int n = graph.size();
    vector<int> indegree = compute_indegree(graph);

    queue<int> ready;
    // initiate with 0-indegree courses:
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

int main() {
    //lexi_order_test();

    min_semesters_test();

    return 0;
}