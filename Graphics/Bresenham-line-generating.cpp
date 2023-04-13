#include <iostream>
#include <vector>

using namespace std;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {
    }

    void read() { cin >> x >> y; }

    Point operator -(Point p) {
        Point res;
        res.x = x - p.x;
        res.y = y - p.y;

        return res;
    }
};

vector<Point> generate_line(Point start, Point end) {
    int deltaX = end.x - start.x,
            deltaY = end.y - start.y;

    vector<Point> line = {start};
    int p = 2 * deltaY - deltaX; // Po

    int number_of_points = deltaX;
    while (number_of_points--) {
        Point next;
        if (p < 0) {
            next = {line.back().x + 1, line.back().y};
            p += (2 * deltaY);
        }
        else {
            next = {line.back().x + 1, line.back().y + 1};
            p += (2 * deltaY - 2 * deltaX);
        }
        line.push_back(next);
    }

    return line;
}

void print(vector<Point>& line) {
    cout << "\nYour Bresenham's Line:\n";
    for (Point p : line) {
        cout << p.x << ' ' << p.y << endl;
    }
}
int main() {
    // take start and end points:
    Point start, end;
    cout << "Enter the start point:\n";
    start.read();
    cout << "Enter the end point:\n";
    end.read();

    vector<Point> line = generate_line(start, end);
    print(line);

    return 0;
}