#include <iostream>
#include <vector>

using namespace std;

/*
 * in-place algo
 * not adaptive => best, worst, average analysis are same
 * not stable (we can make it stable by using the shift idea.. but this will make it more slow :)
 * not online
 */

int operations;

template <typename type>
void selection_sort(vector<type>& vec) { // O(n^2)
    int n = vec.size();
    for (int i = 0; i < n; ++i) {
        int nxtMin = i;
        for (int j = i + 1; j < n; ++j) {
            if (vec[j] < vec[nxtMin])
                nxtMin = j;

            ++operations;
        }
        swap(vec[i], vec[nxtMin]);
    }
}

//////////////////// test & main ////////////////////

void print(vector<int>& vec) {
    for (int& i : vec)
        cout << i << ' ';
    cout << endl;
}
void test() {
    vector<int> sorted = {1, 2, 3, 5, 7, 10};
    operations = 0;
    selection_sort(sorted);
    cout << "operations for already sorted = " << operations << endl; // 15

    vector<int> v1 = {1, 5, 4, 3, 7, 10};
    selection_sort(v1);
    print(v1);

    vector<int> reversed = {10, 7, 5, 3, 2, 1};
    operations = 0;
    selection_sort(reversed);
    cout << "operations for reversed = " << operations << endl; // 15
    // notice that it's NOT adaptive algo

}

int main()
{
    test();

    return 0;
}