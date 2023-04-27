#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset

using namespace std;

/// https://leetcode.com/problems/filling-bookcase-shelves/

const int MAX = 1000;
int memory[MAX];

class Solution {
    int shelf_width;
    vector<vector<int>> books;
    int n;
public:
    int dp_min_height(int idx = 0) {
        if (idx == n)
            return 0;

        auto& ret = memory[idx];
        if (ret != -1)
            return ret;

        // next choices
        int width = shelf_width,
            height = 0;
        ret = INT_MAX; // to minimize

        for (int cur = idx; cur < n; ++cur) {
            auto book = books[cur];
            if (width < book[0])
                break;

            width -= book[0];
            height = max(height, book[1]);
            int newSplit = dp_min_height(cur + 1);
            ret = min(ret, height + newSplit); // move to a new shelf
        }

        return ret;
    }
    int minHeightShelves(vector<vector<int>>& _books, int shelfWidth) {
        memset(memory, -1, sizeof(memory));
        shelf_width = shelfWidth;
        books = _books;
        n = _books.size();

        return dp_min_height();
    }
};

int main() {
    Solution sol;
    vector<vector<int>> books = {{1, 1}, {2, 3}, {2, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 2}};
    int w = 4;
    cout << sol.minHeightShelves(books, w);

    return 0;
}