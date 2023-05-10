/// https://leetcode.com/problems/powx-n/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    double myPow(double x, long long n) {
        if (n < 0) {
            x = 1/x;
            n = -n;
        }
        else if (n == 0)
            return 1;
        else if (n == 1)
            return x;

        int half = n / 2;
        double res = myPow(x, half);
        res *= res;
        res *= myPow(x, n%2);
        return res;
    }
};

int main() {


    return 0;
}