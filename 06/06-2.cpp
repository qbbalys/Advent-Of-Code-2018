#include <iostream>
#include <vector>

using namespace std;

struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

void readInput(vector<Point> &points) {
    int x, y;
    char c;
    
    while (cin >> x >> c >> y) {
        points.push_back(Point(x, y));
    }
}

int sumDists(int x, int y, const vector<Point> &points) {
    int distanceSum = 0;
    for (int i = 0; i < points.size(); ++i) {
        distanceSum += abs(x - points[i].x) + abs(y - points[i].y);
    }

    return distanceSum;
}

int solve(const vector<Point> &points) {
    int maxX = 0, maxY = 0;

    for (const Point &p : points) {
        if (p.x > maxX) maxX = p.x;
        if (p.y > maxY) maxY = p.y;
    }

    ++maxX;
    ++maxY;

    int area = 0;
    bool grid[maxX][maxY];
    memset(grid, 0, sizeof(grid));
    
    for (int y = 0; y < maxY; ++y) {
        for (int x = 0; x < maxX; ++x) {
            int sum = sumDists(x, y, points);
            if (sum < 10000) {
                grid[x][y] = true;
                ++area;
            }
        }
    }

    // for (int y = 0; y < maxY; ++y) {
    //     for (int x = 0; x < maxX; ++x) {
    //         cout << grid[x][y];
    //     }
    //     cout << endl;
    // }

    return area;
}


int main() {
    vector<Point> points;
    readInput(points);
    cout << solve(points) << endl;
    return 0;
}