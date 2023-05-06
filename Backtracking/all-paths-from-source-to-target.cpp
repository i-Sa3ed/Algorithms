#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset

using namespace std;

/// https://leetcode.com/problems/all-paths-from-source-to-target/

const int MAX = 15;
bool visited[MAX]; // shared state
class Solution {
    int n;
    vector<int> path;
    vector< vector<int> > allPaths;
    vector<vector<int>> graph;
public:
    void find_paths(int node = 0) {
        if (node == n-1) {
            path.push_back(node); // add it
            allPaths.push_back(path);
            path.pop_back(); // undo
            return;
        }

        // update
        path.push_back(node);
        visited[node] = true;

        for (int neighbor : graph[node])
            if (!visited[neighbor])
                find_paths(neighbor);

        // undo
        visited[node] = false;
        path.pop_back();
    }
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& _graph) {
        graph = _graph;
        n = graph.size();
        memset(visited, false, sizeof(visited));

        find_paths(0);

        return allPaths;
    }
};

int main() {

    return 0;
}