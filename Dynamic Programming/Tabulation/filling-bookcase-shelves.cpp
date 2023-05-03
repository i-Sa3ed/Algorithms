#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset

using namespace std;

/// https://leetcode.com/problems/filling-bookcase-shelves/
// we solved it before using Memoization
// let's do it now by Tabulation ;)

const int MAX = 1000;
int memory[MAX];

class Solution {
public:
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        memset(memory, -1, sizeof(memory));

        int n = books.size();

        // major loop
        for (int idx = 0; idx < n; ++idx) {
            int& min_height = memory[idx];
            int width = shelfWidth,
                    height = 0;
            min_height = INT_MAX; // to minimize

            for (int cur = idx; cur >= 0; --cur) {
                auto book = books[cur];
                if (width < book[0]) // can't add this book to this shelf, No more available width
                    break;

                width -= book[0];
                height = max(height, book[1]);

                int newSplit = 0;
                if (cur > 0) // Observe: Base case
                    newSplit = memory[cur - 1];

                min_height = min(min_height, height + newSplit);
            }
        }

        return memory[n-1];
    }
};

int main() {

    return 0;
}