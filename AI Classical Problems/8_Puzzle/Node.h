
#ifndef ALGO_CODES_NODE_H
#define ALGO_CODES_NODE_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

class Node {

public:
    // not preferred practice, but for simplicity :)

    vector<Node*> children;
    vector<int> puzzle;
    Node *parent;

    Node(vector<int> _puzzle, Node *_parent);
    virtual ~Node();

    void print_puzzle();
    int get_zero_idx();
    void move_up();
    void move_down();
    void move_right();
    void move_left();
};


#endif //ALGO_CODES_NODE_H
