#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <map>
#include <valarray>

using namespace std;

/// https://leetcode.com/problems/binary-search/
int search(vector<int>& nums, int target) {
    int res = -1;
    int l = 0, r = nums.size() - 1;
    while (l <= r) {
        int m = l + (r - l) / 2; // to avoid overflow
        if (nums[m] == target) {
            res = m;
            break;
        } else if (target > nums[m]) // search on the right side
            l = m + 1;
        else // search on the left side
            r = m - 1;
    }

    return res;
}


/// equal range:
// returns both lower and upper bounds for a value

/// https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
// using my own binary search function
int find_first(vector<int>& nums, int val) {
    int res = -1;
    int start = 0, end = nums.size() - 1;
    while (start <= end) {
        int m = start + (end - start) / 2;
        if (nums[m] == val) {
            res = m;
            end = m - 1; // minimize as you can
        }
        else if (val > nums[m])
            start = m + 1;
        else
            end = m - 1;
    }

    return res;
}
int find_last(vector<int>& nums, int val) {
    int res = -1;
    int start = 0, end = nums.size() - 1;
    while (start <= end) {
        int m = start + (end - start) / 2;
        if (nums[m] == val) {
            res = m;
            start = m + 1; // maximize as you can
        }
        else if (val > nums[m])
            start = m + 1;
        else
            end = m - 1;
    }

    return res;
}
vector<int> searchRange_(vector<int>& nums, int target) {
    vector<int> res(2);
    res[0] = find_first(nums, target);
    res[1] = find_last(nums, target);

    return res;
}

// using "equal range" function
vector<int> searchRange(vector<int>& nums, int target) {
    vector<int> res = {-1, -1};

    // use equal_range function
    auto range = equal_range(nums.begin(), nums.end(), target);
    if (range.first != range.second) // exist
        res[0] = range.first - nums.begin(), res[1] = range.second - nums.begin() - 1;

    return res;
}


/// https://leetcode.com/problems/find-right-interval/
// using my binary search function:
vector<int> findRightInterval(vector<vector<int>>& intervals) {
    int n = intervals.size();
    vector< pair<int, int> > starts; // starts, indices
    for (int i = 0; i < n; ++i) {
        starts.push_back({intervals[i][0], i});
    }

    sort(starts.begin(), starts.end()); // sort based on start points

    vector<int> rights;
    for (int i = 0; i < n; ++i) { // O(n logn)
        // binary search for the right interval
        int end = intervals[i][1];
        int l = 0, r = n - 1;
        int idx = -1;
        while (l <= r) {
            int m = l + (r - l)/2;
            if (starts[m].first >= end)
                idx = starts[m].second, r = m - 1;
            else
                l = m + 1;
        }
        rights.push_back(idx);
    }

    return rights;
}

// using STL binary search:
vector<int> findRightInterval_2(vector<vector<int>>& intervals) {
    int n = intervals.size();
    vector< pair<int, int> > starts; // starts, indices
    for (int i = 0; i < n; ++i) {
        starts.push_back({intervals[i][0], i});
    }

    sort(starts.begin(), starts.end()); // sort based on start points

    vector<int> rights;
    for (int i = 0; i < n; ++i) { // O(n logn)
        // binary search for the right interval
        int end = intervals[i][1];

        // 0 => dummy index, doesn't affect the search, because the start indexes are unique
        auto it = lower_bound(starts.begin(), starts.end(), make_pair(end, 0));

        if (it == starts.end())
            rights.push_back(-1);
        else
            rights.push_back(it->second);
    }

    return rights;
}

// using map:
vector<int> findRightInterval_3(vector<vector<int>>& intervals) {
    int n = intervals.size();
    map< int, int > startToIdx;
    for (int i = 0; i < n; ++i) {
        startToIdx.insert({intervals[i][0], i});
    }

    vector<int> rights(n, -1);
    for (int i = 0; i < n; ++i) {
        auto it = startToIdx.lower_bound(intervals[i][1]);
        if (it != startToIdx.end())
            rights[i] = it->second;
    }

    return rights;
}


/// https://leetcode.com/problems/valid-triangle-number/
// using my own binary search
int triangleNumber(vector<int>& nums) {
    const int n = nums.size();
    sort(nums.begin(), nums.end());

    unsigned int ans = 0;
    for (int mx = n - 1; mx >= 2; --mx) {
        for (int mid = mx - 1; mid >= 1; --mid) {
            // binary search for min valid side
            int l = 0, r = mid - 1;
            int mn = mid;
            while (l <= r) {
                int m = l + (r-l) / 2;
                if (nums[m] + nums[mid] > nums[mx])
                    mn = m, r = m - 1;
                else
                    l = m + 1;
            }
            ans += (mid - mn);
        }
    }

    return ans;
}

// using stl binary search
int triangleNumber_stl(vector<int>& nums) {
    const int n = nums.size();
    sort(nums.begin(), nums.end());

    unsigned int ans = 0;
    for (int mx = n - 1; mx >= 2; --mx) {
        for (int mid = mx - 1; mid >= 1; --mid) {
            // binary search for min valid side
            auto it = upper_bound(nums.begin(), nums.begin() + mid, nums[mx] - nums[mid]);
            int pos = it - nums.begin();
            ans += (mid - pos);
        }
    }

    return ans;
}


/// https://leetcode.com/problems/arranging-coins/
long long sum_to_n(int n) { return (1LL * n * (n + 1) / 2); }
int arrangeCoins(int n) {
    int l = 1, r = n;
    int ans = 1;
    while (l <= r) {
        int m = l + (r-l) / 2;
        if (sum_to_n(m) <= n)
            ans = m, l = m + 1;
        else
            r = m - 1;
    }

    return ans;
}


/// https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/
bool possible(vector<int>& nums, int threshold, int div) {
    long long sum = 0;
    for (int i : nums) {
        sum += (ceil(double(i) / div));
    }

    return sum <= threshold;
}
int smallestDivisor(vector<int>& nums, int threshold) {
    int mn = 1, mx = *max_element(nums.begin(), nums.end());
    int ans;
    while (mn <= mx) {
        int mid = mn + (mx - mn) / 2;
        if (possible(nums, threshold, mid))
            ans = mid, mx = mid - 1;
        else
            mn = mid + 1;
    }

    return ans;
}


/// https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/
bool possible(vector<int>& bloomDay, int m, int k, int days) {
    // compute bouquets:
    const int n = bloomDay.size();
    int adj = 0, bouquets = 0;
    for (int i = 0; i < n; ++i) {
        if (bloomDay[i] <= days)
            ++adj;
        else
            adj = 0;

        if (adj == k) {
            ++bouquets;
            adj = 0;
        }

        if (bouquets >= m)
            return true; // more efficient to stop early
    }

    //cout << "day: " << days << "  bouquets: " << bouquets << endl;

    return false;
}
int minDays(vector<int>& bloomDay, int m, int k) {
    const int n = bloomDay.size();
    if (1LL * m * k > n)
        return -1;

    int mn = 1, mx = *max_element(bloomDay.begin(), bloomDay.end());
    int ans;
    while (mn <= mx) {
        int mid = mn + (mx - mn) / 2;
        if (possible(bloomDay, m, k, mid))
            ans = mid, mx = mid - 1;
        else
            mn = mid + 1;
    }
    return ans;
}


/// https://leetcode.com/problems/heaters/
bool possible(vector<int>& houses, vector<int>& heaters, int rad) {
    int p1, p2;
    p1 = p2 = 0; // 2 pointers

    int mnRad;
    while (p1 < houses.size()) {
        mnRad = abs(houses[p1] - heaters[p2]);
        while (p2 < heaters.size() - 1 and
                abs(houses[p1] - heaters[p2+1]) <= mnRad) {
            ++p2;
            mnRad = abs(houses[p1] - heaters[p2]);
        }

        int x = houses[p1], y = heaters[p2];

        if (mnRad > rad)
            return false;

        ++p1;
    }

    cout << mnRad << endl;

    return true;
}
int findRadius(vector<int>& houses, vector<int>& heaters) {
    // I don't know if vectors are sorted or not..
    if (!is_sorted(houses.begin(), houses.end()))
        sort(houses.begin(), houses.end());
    if (!is_sorted(heaters.begin(), heaters.end()))
        sort(heaters.begin(), heaters.end());

    int mn = 0, mx = 1000000000;
    int ans;
    while (mn <= mx) {
        int mid = mn + (mx - mn) / 2;
        if (possible(houses, heaters, mid))
            ans = mid, mx = mid - 1;
        else
            mn = mid + 1;
    }

    return ans;
}


//////////////////// binary search on real values ////////////////////
double f(double x) {
    return 4 * pow(x, 7) + 3 * pow(x, 5) - 1000;
}
double binary_search_real(double EPS = 1e-9) {
    double start = 0, end = 3;
    while (fabs(end - start) > EPS) { // use fabs => to avoid any unexpected behavior
        double mid = start + (end - start) / 2;
        if (f(mid) < 0)
            start = mid; // notice the difference in updating
        else if (f(mid) > 0)
            end = mid;
    }

    return start; // not found
}
/** Notes for CP:
 * instead of using comparison with EPS, we can iterate over a specific number
 * in some problems, we need to add EPS to the result (e.g. return start + EPS)
 */

/// https://leetcode.com/problems/sqrtx/
int mySqrt(int x) {
    int start = 0, end = x;
    int ans;
    for (int i = 1; i <= 40; ++i) {
        long long mid = start + (end - start) / 2;
        if (mid * mid <= x)
            start = mid + 1, ans = mid; // maximize ans
        else
            end = mid - 1;
    }

    //cout << start << ' ' << end << endl;
    return ans;
}

/// https://www.spoj.com/problems/PIE/
double area(double rad) {
    return M_PI * rad * rad;
}
bool possible(double v, int n, int f, vector<int>& r) {
    int available = 0;
    for (int i = 0; i < n; ++i) {
        available += int(area(r[i]) / v);
        if (available > f)
            return true;
    }
    return false;
}
double largest_area() {
    int n, f;
    cin >> n >> f;
    vector<int> r(n);
    for (int i = 0; i < n; ++i) {
        cin >> r[i];
    }
    sort(r.begin(), r.end(), greater<>()); // n logn

    // binary search
    double start = 0, end = area(r[0]);
    for (int i = 1; i <= 100; ++i) {
        double mid = start + (end - start) / 2;
        if (possible(mid, n, f, r))
            start = mid;
        else
            end = mid;
    }
    return start;
}


/// https://www.spoj.com/problems/GLASNICI/
bool possible(double k, int n, vector<double>& d, double canMove) {
    double lastPos = d[0] + canMove;
    for (int i = 1; i < d.size(); ++i) {
        double lastMsgPos = lastPos + k;
        if (lastMsgPos < d[i] - canMove)
            return false;
        lastPos = min(lastMsgPos, d[i] + canMove);
    }
    return true;
}
double min_time() {
    double k; cin >> k;
    int n; cin >> n;
    vector<double> d(n);
    for (int i = 0; i < n; ++i) {
        cin >> d[i];
    }

    // binary search on min time.
    // minimization
    double start = 0, end = 1e9;
    for (int i = 1; i <= 100; ++i) { // not sure if enough :)
        double mid = start + (end - start) / 2;
        if (possible(k, n, d, mid))
            end = mid;
        else
            start = mid;
    }
    return end;
}


////////////////////////////////////////////////////
int mylog(int base = 2, int x = 48828125) {
    int res = 0;
    while (x > 1)
        ++res, x /= base;
    return res;
}

void test() {
     cout << mylog(5) << endl;
     cout << log(48828125) / log(5) << endl;
}

int main()
{
    test();

    return 0;
}