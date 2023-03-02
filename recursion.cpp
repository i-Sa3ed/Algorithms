#include <iostream>
#include <cassert>

using namespace std;

struct Review {
    // here are some basic example to review the recursion concepts
    void print_triangle_reversed(int levels) {
        if (levels == 0) // base case
            return;

        for (int i = 1; i <= levels; ++i) {
            cout << "#";
        }
        cout << endl;

        print_triangle_reversed(levels - 1);
    }

    void print_triangle(int levels) {
        if (levels == 0)
            return;

        print_triangle(levels - 1);

        for (int i = 1; i <= levels; ++i) {
            cout << "*";
        }
        cout << endl;
    }

    void print_3n_plus_1(int n) {
        cout << n << ' ';

        if (n == 1)
            return;
        else if (n & 1) // odd
            print_3n_plus_1(3*n + 1);
        else // even
            print_3n_plus_1(n / 2);
    }

};

struct Easy {
    // here are some easy challenges

    int length_3n_plus_1(int n) {
        if (n == 1)
            return 1;
        else if (n & 1)
            return 1 + length_3n_plus_1(3*n + 1);
        else
            return 1 + length_3n_plus_1(n / 2);
    }

    long long my_pow(int value, int p = 2) {
        // p = 2 => obtain square by default
        assert(p >= 0);

        if (p == 0)
            return 1;

        return value * my_pow(value, p - 1);
    }

    /// arrays manipulation
    int arr_max(int arr[], int len) {
        assert(len > 0);

        if (len == 1)
            return arr[0];

        return max(arr[len-1], arr_max(arr, len - 1));
        // compare with the elements on my right side..
    }
    long long arr_sum(int arr[], int len) {
        if (len == 0)
            return 0;

        return arr[len-1] + arr_sum(arr, len - 1);
    }
    double average(int arr[], int len) {
        assert(len > 0);

        if (len == 1)
            return arr[0];

        double subResult = average(arr, len - 1);
        subResult *= (len - 1); // it was divided by (len - 1) before it comes here
        // so, multiply it = obtain the sum

        return (subResult + arr[len-1]) / len;
    }
    void arr_increment(int arr[], int len) {
        if (len == 0)
            return;

        arr[len-1] += (len - 1);

        arr_increment(arr, len - 1);
    }
    int accumulate_arr(int arr[], unsigned int len) {
        if (len == 0)
            return 0;

        arr[len-1] += accumulate_arr(arr, len - 1);
        return arr[len-1];
    }
    void left_max(int arr[], int len) {
        assert(len > 0);

        if (len == 1)
            return;

        left_max(arr, len - 1);
        arr[len-1] = max(arr[len-1], arr[len-2]);
    }
};

/////////////////////// test & main ///////////////////////

void test_review() {
    Review rev;

    rev.print_triangle_reversed(5);
    cout << endl;

    rev.print_triangle(5);
    cout << endl;

    rev.print_3n_plus_1(5); cout << endl;
}

void print(int arr[], int n) {
    // utility
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << ' ';
    }
    cout << endl;
}
void test_easy() {
    Easy easy;

    cout << easy.length_3n_plus_1(5) << endl; // 6
    cout << easy.length_3n_plus_1(6) << endl; // 9

    cout << easy.my_pow(12) << endl; // 144
    cout << easy.my_pow(7, 3) << endl; // 343
    cout << easy.my_pow(10, 0) << endl; // 1

    int arr[] = {1, 10, 5, 2, 13, 5};
    cout << easy.arr_max(arr, 6) << endl; // 13
    cout << easy.arr_sum(arr, 6) << endl; // 36
    cout << easy.average(arr, 6) << endl; // 6

    /*easy.arr_increment(arr, 6);
    print(arr, 6);*/

    int arr1[] = {1, 2, 3, 4, 5, 6};
    easy.accumulate_arr(arr1, 6);
    print(arr1, 6);

    easy.left_max(arr, 6);
    print(arr, 6);
}

int main() {
    //test_review();

    test_easy();

    return 0;
}
