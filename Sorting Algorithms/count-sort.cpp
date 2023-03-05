#include <iostream>
#include <vector>

using namespace std;

/*
 * not adaptive
 * not stable
 * not in-place => need extra memory for freq array
 * not online
 */
// it's good for limited range of data
// obvious example => sorting strings

template <typename type>
void count_sort(vector<type>& vec) {
    // time = O(n + MAX)
    // space = O(MAX)

    int n = vec.size();
    type MAX = vec[0], MIN = vec[0];
    for (int i = 1; i < n; ++i) {
        MAX = max(MAX, vec[i]);
        MIN = min(MIN, vec[i]);
    }

    // we also can use a map if the values are far from each others ;)
    vector<int> frq(MAX + 1);
    for (int i = 0; i < n; ++i) {
        frq[vec[i]]++;
    }

    int idx = 0;
    for (int i = MIN; i <= MAX; ++i) { // O(n + MAX) // notice the tricky loops ;)
        for (int j = 0; j < frq[i]; ++j, ++idx) {
            vec[idx] = i;
        }
    }
}


//////////////////// test & main ////////////////////

template <typename type>
void print(vector<type>& vec) {
    int n = vec.size();
    for (int i = 0; i < n; ++i) {
        cout << vec[i] << ' ';
    }
    cout << endl;
}

void test() {
    vector<int> v1 = {1, 2, 1, 1, 3, 4, 5, 2};
    count_sort(v1);
    print(v1);
}

int main()
{
    test();

    return 0;
}