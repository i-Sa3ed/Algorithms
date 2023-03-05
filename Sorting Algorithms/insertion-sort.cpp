#include <iostream>
#include <vector>

using namespace std;

template <typename type>
void insertion_sort(vector<type>& obj) {
    int n = obj.size();
    for (int i = 1; i < n; ++i) {
        int pos = i;
        while (pos > 0 and obj[pos] < obj[pos-1])
            swap(obj[pos], obj[pos-1]), pos--;
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

}

int main() {
    test();

    return 0;
}