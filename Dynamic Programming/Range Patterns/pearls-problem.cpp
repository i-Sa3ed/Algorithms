// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=676
#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;


const int MAX = 100 + 1;
int memory[MAX];

vector<int> quantity, price;

// Find the best split of the array starting from this index
int best_split(int start_idx) {
    if (start_idx >= (int)quantity.size())
        return 0;

    auto &ret = memory[start_idx];
    if (ret != -1)
        return ret;

    // next choices:
    int sum = 10, // the added value
        n = quantity.size();
    ret = INT_MAX; // to minimize it
    for (int end_idx = start_idx; end_idx < n; ++end_idx) {
        sum += quantity[end_idx];
        int choice_cost = price[end_idx] * sum + best_split(end_idx + 1);
        ret = min(ret, choice_cost);
    }
    return ret;
}

int main() {
    //freopen("data.txt", "rt", stdin);

    int cases, n;
    scanf("%d", &cases);

    while (cases--) {
        scanf("%d", &n);
        quantity.resize(n);
        price.resize(n);

        for (int i = 0; i < n; ++i)
            scanf("%d%d", &quantity[i], &price[i]);

        memset(memory, -1, n * sizeof(int));

        printf("%d\n", best_split(0));
    }

    return 0;
}

