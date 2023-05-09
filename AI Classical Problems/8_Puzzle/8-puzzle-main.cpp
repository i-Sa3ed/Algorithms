#include <fstream>
#include "Node.h"

bool contains(queue<Node*> q, Node *node) {
    while (!q.empty()) {
        if (q.front()->puzzle == node->puzzle)
            return true;
        q.pop();
    }
    return false; // not found
}

void trace_rec(vector<Node*>& vec, Node *cur) {
    if (cur == NULL)
        return;

    trace_rec(vec, cur->parent);
    vec.push_back(cur);
}
void trace_solution(vector<Node*> tracer, Node *sol) {
    // 'sol' must be a valid node

    Node *tmp = sol;
    trace_rec(tracer, tmp);

    cout << "Printing Solution..." << endl;
    for (auto node : tracer) {
        node->print_puzzle();
        cout << endl;
    }
}

void print_to_file(queue<Node*> closedList) {
    ofstream fout_nodes;
    fout_nodes.open("Nodes.txt", ios::out);
    closedList.pop(); /// why?!

    int countNodes = 1;
    while (!closedList.empty()) {
        fout_nodes << "\nNode number: " << countNodes;
        for (int i = 0; i < 9; ++i) {
            if (i % 3 == 0)
                fout_nodes << '\n'; // new row
            fout_nodes << closedList.front()->puzzle[i] << ' ';
        }
        fout_nodes << '\n';

        fout_nodes << "Parent: ";
        for (int i = 0; i < 9; ++i) {
            if (i % 3 == 0)
                fout_nodes << '\n'; // new row
            fout_nodes << closedList.front()->parent->puzzle[i] << ' ';
        }

        closedList.pop();
        countNodes++;
    }

    fout_nodes.close();
}

int main() {
    vector<int> initialState = {1, 2, 3, 4, 0, 5, 6, 7, 8};
    vector<int> goalState = {1, 2, 3, 4, 5, 6, 7, 8, 0};

    queue<Node*> openList, closedList;

    Node *init = new Node(initialState, NULL);
    openList.push(init);

    bool foundGoal = false;
    int countExploredNodes = 0;
    vector<Node*> solution;

    cout << "Searching for solution...\n";
    while (!openList.empty() and !foundGoal) {
        Node *curNode = openList.front();
        openList.pop();
        closedList.push(curNode);

        // try all possible moves:
        curNode->move_up();
        curNode->move_down();
        curNode->move_right();
        curNode->move_left();

        for (auto it : curNode->children) {
            Node *child = it;
            if (child->puzzle == goalState) {
                cout << "Goal Found ^-^ \n";
                trace_solution(solution, child);
                foundGoal = true;
            }
            else if (!contains(openList, child) and
                    !contains(closedList, child)) {
                openList.push(child);
            }
        }
        countExploredNodes++;
    }

    cout << "No. of nodes in the closed list = " << countExploredNodes << endl;
    print_to_file(closedList);

    return 0;
}