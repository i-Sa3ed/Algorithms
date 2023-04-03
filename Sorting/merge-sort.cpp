/// https://leetcode.com/problems/sort-list/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
    vector<int> list_to_vector(ListNode* head) {
        ListNode* cur = head;
        vector<int> result;
        while (cur) {
            result.push_back(cur->val);
            cur = cur->next;
        }
        return result;
    }
    ListNode* vector_to_list(vector<int>& vec) {
        ListNode *head = new ListNode(vec[0]), *cur = head;
        for (int i = 1; i < vec.size(); ++i) {
            cur->next = new ListNode(vec[i]);
            cur = cur->next;
        }

        return head;
    }

public:
    vector<int> MERGE(vector<int>& arr1, vector<int>& arr2) {
        const int n1 = arr1.size(), n2 = arr2.size();
        vector<int> result(n1 + n2);
        int i = 0, i1 = 0, i2 = 0;
        for ( ; i1 < n1 and i2 < n2; ++i) {
            if (arr1[i1] <= arr2[i2])
                result[i] = arr1[i1++];
            else
                result[i] = arr2[i2++];
        }

        // copy the remaining from the bigger array:
        // Notice: only one of these loops will operate ;)
        for ( ; i1 < n1; ++i1, ++i)
            result[i] = arr1[i1];
        for ( ; i2 < n2; ++i2, ++i)
            result[i] = arr2[i2];

        return result;
    }
    vector<int> merge_sort(vector<int>& arr, int l, int h) {
        vector<int> half1 = {arr[l]}, // to handle case of (l == h)
                    half2;
        if (l < h) {
            int mid = l + (h-l)/2;
            half1 = merge_sort(arr, l, mid);
            half2 = merge_sort(arr, mid+1, h);
        }
        vector<int> merged = MERGE(half1, half2);
        return merged;
    }
    ListNode* sortList(ListNode* head) {
        if (!head)
            return nullptr;

        // list => vector
        vector<int> arr = list_to_vector(head);

        // sort the vector, using merge sort
        vector<int> sorted = merge_sort(arr, 0, arr.size()-1);

        // vector => list
        ListNode* ans = vector_to_list(sorted);
        return ans;
    }
};

int main() {
    ListNode *head = new ListNode(4);
    ListNode *cur = head;
    cur->next = new ListNode(2); cur = cur->next;
    cur->next = new ListNode(1); cur = cur->next;
    cur->next = new ListNode(3); cur = cur->next;

    ListNode *head1 = nullptr;

    Solution sol;
    ListNode *res = sol.sortList(head1);


    return 0;
}