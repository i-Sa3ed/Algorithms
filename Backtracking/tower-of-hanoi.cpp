/// https://practice.geeksforgeeks.org/problems/tower-of-hanoi-1587115621/1

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset
#include <map>
#include <stack>

using namespace std;

class Solution{
    int N;
    int original_to;

    vector< stack<int> > rods;
    bool done = false, first_call = true;
public:
    void init(int n, int from, int to) {
        N = n;
        original_to = to;

        stack<int> tmp; tmp.push(0);
        rods = vector< stack<int> >(4, tmp);
        for (int i = n; i >= 1; --i) {
            rods[from].push(i);
        }
    }

    long long toh(int n, int from, int to, int aux) {
        if (first_call) {
            init(n, from, to);
            first_call = false;
        }

        if (rods[original_to].size() == N + 1)
            done = true;
        if (done or rods[from].top() == 0)
            return 0;

        bool moved = false;

        long long all_paths = 0;
        if (to != 0 and (rods[to].top() == 0 or rods[to].top() > rods[from].top())) { // from => to
            cout << "move disk " << rods[from].top() << " from rod " << from << " to rod " << to << endl;

            rods[to].push(rods[from].top()); // move to 'to'
            rods[from].pop();
            moved = true;

            all_paths = toh(n, from, to, aux) +
                    toh(n, to, 0, aux) + // use '0' to avoid moving repeatedly (i.e. from => to, to => from) .. which create INF loop
                    toh(n, aux, to, from);
        }
        else if (aux != 0 and (rods[aux].top() == 0 or rods[aux].top() > rods[from].top())) { // from => aux
            cout << "move disk " << rods[from].top() << " from rod " << from << " to rod " << aux << endl;

            rods[aux].push(rods[from].top()); // move to 'aux'
            rods[from].pop();
            moved = true;

            all_paths = toh(n, from, to, aux) +
                    toh(n, aux, 0, to) +
                    toh(n, to, from, aux);
        }
        else {
            all_paths = toh(n, to, from, aux) + toh(n, aux, to, from);
        }

        return (moved + all_paths);
    }

};

int main() {
    int T = 1;
    while (T--) {

        int N;
        cin >> N;//taking input N

        //calling toh() function
        Solution ob;

        cout << ob.toh(N, 1, 3, 2) << endl;
    }
    return 0;
}