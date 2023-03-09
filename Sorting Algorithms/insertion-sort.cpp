#include <iostream>
#include <vector>

using namespace std;

template <typename type>
void insertion_sort(vector<type>& obj, bool des = false) {
    int n = obj.size();
    for (int i = 1; i < n; ++i) {
        int pos = i;
        bool DO = (obj[pos] > obj[pos-1] and des) or (obj[pos] < obj[pos-1] and !des);
        while (DO) {
            swap(obj[pos], obj[pos-1]), pos--;
            DO = pos > 0 and ((obj[pos] > obj[pos-1] and des) or (obj[pos] < obj[pos-1] and !des));
        }
    }
}

///////////////////// test & main /////////////////////

void print(const vector<int>& x) {
    for (int i : x)
        cout << i << ' ';
    cout << endl;
}
void test() {
    vector<int> x = {2, 3, 1, 7, 4};
    insertion_sort(x);
    print(x);

    insertion_sort(x, true);
    print(x);

}

int main() {
    test();

    return 0;
}