/// https://practice.geeksforgeeks.org/problems/fractional-knapsack-1587115620/1

#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

//class implemented
struct Item{
    int value;
    int weight;
};

bool comp(Item it1, Item it2) {
    return (double(it1.value)/it1.weight) > (double(it2.value)/it2.weight);
}

class Solution
{
public:
    //Function to get the maximum total value in the knapsack.
    double fractionalKnapsack(int W, Item arr[], int n)
    {
        // sort the items based on the ratio = value/weight
        sort(arr, arr + n, comp);

        double total = 0;
        for (int i = 0; i < n; ++i) {
            if (W > arr[i].weight) {
                total += arr[i].value;
                W -= arr[i].weight;
            }
            else {
                total += (1.0 * W / arr[i].weight * arr[i].value);
                W = 0;
                break;
            }
        }

        return total;
    }

};


int main() {
    int t;
    //taking testcases
    cin >> t;
    cout << setprecision(2) << fixed;
    while (t--) {
        //size of array and weight
        int n, W;
        cin >> n >> W;

        Item arr[n];
        //value and weight of each item
        for (int i = 0; i < n; i++) {
            cin >> arr[i].value >> arr[i].weight;
        }

        //function call
        Solution ob;
        cout << ob.fractionalKnapsack(W, arr, n) << endl;
    }
    return 0;
}