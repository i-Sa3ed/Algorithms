/// https://www.hackerearth.com/practice/algorithms/sorting/bucket-sort/practice-problems/algorithm/sort-the-array-5/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print(vector<int>& vec) {
    for (int& i : vec)
        cout << i << ' ';
}
int main() {
    int n, k;
    cin >> n >> k;

    // divide into buckets:
    vector<int> buckets[k]; // array of vectors
    for (int i = 0; i < n; ++i) {
        int a; cin >> a;
        int weight = a % k;
        buckets[weight].push_back(a);
    }

    // sort each bucket internally:
    for (int i = 0; i < k; ++i)
        sort(buckets[i].begin(), buckets[i].end());

    // print output:
    for (int bucket = k - 1; bucket >= 0; --bucket) {
        print(buckets[bucket]);
    }

}