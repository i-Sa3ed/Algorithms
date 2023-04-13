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

vector<Point> generate_line(Point start, Point end, vector<int>& parameters) {
    int deltaX = end.x - start.x,
            deltaY = end.y - start.y;

    vector<Point> line;
    int p = 2 * deltaY - deltaX; // Po

    int number_of_points = deltaX;
    Point cur = start;
    while (number_of_points--) {
        parameters.push_back(p);
        Point next;
        if (p < 0) {
            next = {cur.x + 1, cur.y};
            p += (2 * deltaY);
        }
        else {
            next = {cur.x + 1, cur.y + 1};
            p += (2 * deltaY - 2 * deltaX);
        }
        line.push_back(next);
        cur = next;
    }

    return line;
}

void print(vector<int>& paras, vector<Point>& line) {
    cout << "P_k\tPoint_k+1\n";
    for (int i = 0; i < paras.size(); ++i) {
        cout << paras[i] << '\t' << '(' << line[i].x << ", " << line[i].y << ")\n";
    }
}
int main() {
    // take start and end points:
    Point start, end;
    cout << "Enter the start point:\n";
    start.read();
    cout << "Enter the end point:\n";
    end.read();

    vector<int> parameters;
    vector<Point> line = generate_line(start, end, parameters);
    print(parameters, line);

    return 0;
}