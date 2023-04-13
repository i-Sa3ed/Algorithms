#include <iostream>
#include <vector>

using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {
    }

    void read() { cin >> x >> y; }

    Point operator -(Point p) {
        Point res;
        res.x = x - p.x;
        res.y = y - p.y;

        return res;
    }
};

// generates the first octant of a circle centered at origin (0,0)
vector<Point> generate_circle(int r, vector<int>& parameters) {
    Point cur = {0, r}; // initial
    vector<Point> circle;
    int p = 1 - r; // Po

    while (cur.x < cur.y) {
        parameters.push_back(p);
        Point next;
        if (p < 0) {
            next = {cur.x + 1, cur.y};
            p += (2 * next.x + 1);
        }
        else {
            next = {cur.x + 1, cur.y - 1};
            p += (2 * next.x + 1 - 2 * next.y);
        }
        circle.push_back(next);
        cur = next;
    }

    return circle;
}

void print(vector<int>& paras, vector<Point>& circle) {
    cout << "P_k\tPoint_k+1\n";
    for (int i = 0; i < paras.size(); ++i) {
        cout << paras[i] << '\t' << '(' << circle[i].x << ", " << circle[i].y << ")\n";
    }
}
int main() {
    // take radius:
    cout << "Enter the radius of the circle:\n";
    int r; cin >> r;

    vector<int> parameters;
    vector<Point> circle = generate_circle(r, parameters);
    print(parameters, circle);

    return 0;
}