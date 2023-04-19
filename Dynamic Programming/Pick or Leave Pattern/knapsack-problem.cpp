#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

/// Brute-Force
// is strongly related with DP

// recursively generate all possible subsets
string bin;
int cnt = 1;
void generate_subsets(int curIdx) {
    if (curIdx < 0){
        cout << cnt << "- " << bin << '\n';
        ++cnt;
        return;
    }

    // pick:
    bin[curIdx] = '1';
    generate_subsets(curIdx-1);

    // leave:
    bin[curIdx] = '0';
    generate_subsets(curIdx-1);

    bin[curIdx] = ' ';
}

/// Knapsack problem with DP
int s, n;
struct item { int size, val; };
vector< item > items;

// stores: state(idx, limit) => max_benefit
map< pair<int, int>, long long > memory;

long long knapsack(int idx, int limit) {
    /*
     * time: O(n * max_weight)
     * memory: same
     *      we can improve it to O(w) only, by writing it iteratively.
     * max recursion depth limit: n
     */

    // base case
    if (idx >= n)
        return 0;

    pair<int, int> state = {idx, limit};
    if (memory.find(state) != memory.end()) // memoization
        return memory[state];

    // pick (if possible)
    long long pick_choice = 0;
    if (items[idx].size <= limit) {
        pick_choice = items[idx].val + knapsack(idx+1, limit - items[idx].size);
    }

    // leave
    long long leave_choice = knapsack(idx+1, limit);

    return memory[state] = max(pick_choice, leave_choice);

    /// lesson:
    // we store the state, which is a combination of the arguments
    // not only one of them.
}
void solve_knapsack() {
    cin >> s >> n;
    items.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> items[i].size >> items[i].val;
    }

    cout << knapsack(0, s);
}

int main() {
    solve_knapsack();

    return 0;
}