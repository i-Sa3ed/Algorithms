#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset
#include <numeric>

using namespace std;

/// https://leetcode.com/problems/query-kth-smallest-trimmed-number/

class Solution {
    vector<string> nums;
    int n, len;

    vector<int> idxArr;
    int last_digit;

public:
    void count_sort(int key, vector<int>& indices) {
        int count[10] = {0};
        // fill count:
        for (int i = 0; i < n; ++i) {
            string num = nums[indices[i]];
            count[num[key] - '0']++;
        }
        // accumulate count:
        for (int i = 1; i < 10; ++i) {
            count[i] += count[i-1];
        }

        vector<int> output(n);
        for (int i = n - 1; i >= 0; --i) {
            int idx = indices[i];
            string num = nums[idx];
            output[--count[num[key] - '0']] = idx;
        }

        indices = output; // update 'indices' to use it in the next pass
    }
    int radix_sort(int trim, int k) {
        for (; last_digit >= len - trim; --last_digit)
            count_sort(last_digit, idxArr);
        return idxArr[k-1]; // k-1 => 0-based
    }
    vector<int> smallestTrimmedNumbers(vector<string>& _nums, vector<vector<int>>& queries) { // O(d * n)
        nums = _nums;
        n = nums.size(), len = nums[0].size();

        idxArr = vector<int>(n);
        iota(idxArr.begin(), idxArr.end(), 0); // initialize with {0, 1, 2, ... , n-1}
        last_digit = len - 1;

        /// sorted queries
        // the idea is to sort the queries based on 'trim' to avoid TLE
        // by sorting it, we just do the count sort for each digit at most once

        int q = queries.size();
        vector< vector<int> > sorted_queries(q);
        for (int i = 0; i < q; ++i) {
            sorted_queries[i] = {queries[i][1], queries[i][0], i}; // {trim, k, original index}
        }
        sort(sorted_queries.begin(), sorted_queries.end());

        vector<int> answer(q);
        for (int i = 0; i < q; ++i) {
            vector<int> query = sorted_queries[i];
            int q_ans = radix_sort(query[0], query[1]);
            answer[query[2]] = q_ans; // query[2] = original index
        }
        return answer;
    }
};

int main() {
    Solution solution;
    vector<string> nums = {"102", "473", "251", "814"};
    vector< vector<int> > queries = {{ 1, 1 },{ 2, 3 },{ 4, 2 },{ 1, 2 }};
    vector<int> answers = solution.smallestTrimmedNumbers(nums, queries);


    return 0;
}