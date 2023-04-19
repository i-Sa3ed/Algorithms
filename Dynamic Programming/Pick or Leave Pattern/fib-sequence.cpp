#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cstring>

using namespace std;

typedef long long ll;

// build a recursive fib sequence, test # calls_of_10

/// Top-down approach
// to solve the problem of exponential time, we should store the results and REUSE it
const int MAX = 81;
ll memory[MAX];
int calls = 0;
ll fib(int n) {
    ++calls;
    if (n == 0 or n == 1)
        return 1;

    ll &ref = memory[n]; // more common in CP

    if (ref != -1)
        return ref;

    return ref = fib(n - 1) + fib(n - 2); // store, then return
}

/// Bottom-up approach
ll fib2(int n) {
    ll Fib[MAX] = {1, 1}; // base cases
    for (int i = 2; i < MAX; ++i) {
        Fib[i] = Fib[i-1] + Fib[i-2];
    }

    return Fib[n];
}
ll fib3(int n) {
    // just O(1) memory
    if (n == 0 or n == 1)
        return 1;

    ll a = 1, b = 1, c = -1; // base cases
    for (int i = 2; i <= n; ++i) {
        c = a + b;
        a = b, b = c;
    }
    return c;
}

int main() {
    // initialize faster
    memset(memory, -1, sizeof(memory));

    cout << fib3(6) << endl;
    return 0;
}