/// https://practice.geeksforgeeks.org/problems/tower-of-hanoi-1587115621/1

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset
#include <map>
#include <stack>

using namespace std;

class Solution{

public:
    long long toh(int n, int from, int to, int aux) {
        if (n == 0)
            return 0;

        long long res = 1;
        res += toh(n-1, from, aux, to); // move top (n-1) disks: from => aux
        cout << "move disk " << n << " from rod " << from << " to rod " << to << endl;
        res += toh(n-1, aux, to, from); // move the (n-1) disks that put previously: aux => to

        return res;
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