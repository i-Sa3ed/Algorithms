#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset

using namespace std;
using ll = long long;

/// https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1558

string s;
const int MAX = 60;
ll memory[MAX][MAX];

ll dp_count(int left = 0, int right = s.size() - 1) {
    if (left > right)
        return 0;

    auto& ret = memory[left][right];
    if (ret != -1)
        return ret;

    if (left == right)
        return ret = 1;
    else if (left == right - 1)
        return ret = 2 + (s[left] == s[right]);

    // next
    if (s[left] == s[right])
        ret = 1 + dp_count(left + 1, right - 1);
    else ret = 0;

    ll remove_left = dp_count(left + 1, right);  // either remove the left char
    ll remove_right = dp_count(left, right - 1); // or remove the right one
    ll duplicates = dp_count(left + 1, right - 1);
    ret += (remove_left + remove_right - duplicates);

    return ret;
}
void solve() {
    cin >> s;
    memset(memory, -1, sizeof(memory));
    cout << dp_count() << endl;
}
int main() {
    int tc; cin >> tc;
    while (tc--) {
        solve();
    }

    return 0;
}