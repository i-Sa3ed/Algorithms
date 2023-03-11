#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

/*
 * not adaptive
 * not stable
 * not in-place => need extra memory for freq array
 * not online
 */
// it's good for limited range of data
// obvious example => sorting strings

void count_sort(vector<int>& vec) {
    // time = O(n + MAX)
    // space = O(MAX)

    int n = vec.size();
    int MAX = vec[0], MIN = vec[0];
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

/// count sort for negative values
// https://leetcode.com/problems/sort-an-array/

/// count sort for range
// https://leetcode.com/problems/sort-an-array/
// make it min-based


void count_sort(vector<string>& array, int comparisonChars = 1) {
    // comparison chars => number of chars we compare by them..
    // stable algorithm

    map<string, vector<string>> count;
    for (string& str : array) {
        count[str.substr(0, comparisonChars)].push_back(str); // push back => stability
    }

    int idx = 0;
    for (auto& it : count)
        for (string& str : it.second)
            array[idx++] = str;

}

vector<int> count_sort2(vector<int>& array) {
    // another popular approach to create a stable count sort
    // but need extra memory (not in-place)

    int size = array.size();
    if (size <= 1) // already sorted
        return array;

    // obtain max value:
    int MAX = array[0];
    for (int i = 1; i < size; ++i) {
        MAX = max(MAX, array[i]);
    }

    // compute frq:
    vector<int> count(MAX + 1);
    for (int i = 0; i < size; ++i) {
        count[array[i]]++;
    }

    // accumulate frq:
    for (int i = 1; i <= MAX; ++i) {
        count[i] += count[i-1];
    }

    vector<int> output(size);
    for (int i = size - 1; i >= 0; --i) {
        // must loop backward to obtain stable output

        output[count[array[i]] - 1] = array[i];
        --count[array[i]];
    }
    return output;
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

void int_sort_test() {
    vector<int> v1 = {1, 2, 1, 1, 3, 4, 5, 2};
    count_sort(v1);
    print(v1);
}

void string_sort_test() {
    vector<string> names = {"ziad", "belal", "adam", "baheir", "ali"};
    count_sort(names);
    print(names);

    vector<string> prefixes = {"axz", "axa", "zzz", "abc", "abe"};
    count_sort(prefixes, 2);
    print(prefixes);
}

void count_sort2_test() {
    vector<int> vec = {9, 5, 3, 9, 5, 9, 7};
    auto sorted = count_sort2(vec);

    print(vec);
    print(sorted);
}

int main()
{
    //int_sort_test();

    //string_sort_test();

    count_sort2_test();

    return 0;
}