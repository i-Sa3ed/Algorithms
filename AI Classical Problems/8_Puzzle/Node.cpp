#include "node.h"

Node::Node(vector<int> _puzzle, Node *_parent) {
    puzzle = _puzzle;
    parent = _parent;
}

Node::~Node() {
    // Destructor implementation
}

void Node::print_puzzle() {
    for (int i = 0; i < 9; ++i) {
        if (i % 3 == 0)
            cout << '\n'; // new row
        cout << puzzle[i] << ' ';
    }
}

int Node::get_zero_idx() {
    // Implementation of getting the index of the 0 in the puzzle vector
    int zPos = find(puzzle.begin(), puzzle.end(), 0) - puzzle.begin();
    return zPos;
}

/// we can avoid copying and pasting by make a more general function.
// but there's no time :)

void Node::move_up() {
    // Implementation of moving the 0 up in the puzzle vector
    int zPos = get_zero_idx();
    vector<int> newPuzzle = puzzle;
    if (zPos >= 3) // not in the first row ?
        swap(newPuzzle[zPos], newPuzzle[zPos - 3]);

    Node *child = new Node(newPuzzle, this);
    children.push_back(child);
}

void Node::move_down() {
    // Implementation of moving the 0 down in the puzzle vector
    int zPos = get_zero_idx();
    vector<int> newPuzzle = puzzle;
    if (zPos < 6) // not in the last row ?
        swap(newPuzzle[zPos], newPuzzle[zPos + 3]);

    Node *child = new Node(newPuzzle, this);
    children.push_back(child);
}

void Node::move_right() {
    // Implementation of moving the 0 right in the puzzle vector
    int zPos = get_zero_idx();
    vector<int> newPuzzle = puzzle;
    if (zPos != 2 and zPos != 5 and zPos != 8) // not in the right column ?
        swap(newPuzzle[zPos], newPuzzle[zPos + 1]);

    Node *child = new Node(newPuzzle, this);
    children.push_back(child);
}

void Node::move_left() {
    // Implementation of moving the 0 left in the puzzle vector
    int zPos = get_zero_idx();
    vector<int> newPuzzle = puzzle;
    if (zPos != 0 and zPos != 3 and zPos != 6) // not in the left column ?
        swap(newPuzzle[zPos], newPuzzle[zPos - 1]);

    Node *child = new Node(newPuzzle, this);
    children.push_back(child);
}