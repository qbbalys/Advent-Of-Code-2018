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

int nearestPoint(int x, int y, const vector<Point> &points) {
    int nearestPointIndex = 0;
    int nearestPointDistance = INT_MAX;
    int equalDistCount = 1;

    for (int i = 0; i < points.size(); ++i) {
        int distance = abs(x - points[i].x) + abs(y - points[i].y);
        if (distance == nearestPointDistance) ++equalDistCount;
        if (distance < nearestPointDistance) {
            nearestPointDistance = distance;
            nearestPointIndex = i + 1;
            equalDistCount = 1;
        }
    }

    return equalDistCount > 1 ? 0 : nearestPointIndex;
}

int solve(const vector<Point> &points) {
    int maxX = 0, maxY = 0;

    for (const Point &p : points) {
        if (p.x > maxX) maxX = p.x;
        if (p.y > maxY) maxY = p.y;
    }

    ++maxX;
    ++maxY;

    int grid[maxX][maxY];
    memset(grid, 0, sizeof(grid));

    int areas[points.size() + 1];
    memset(areas, 0, sizeof(areas));

    for (int y = 0; y < maxY; ++y) {
        for (int x = 0; x < maxX; ++x) {
            int point = nearestPoint(x, y, points);
            grid[x][y] = point;
            areas[point]++;
        }
    }

    for (int x = 0; x < maxX; ++x) {
        areas[grid[x][0]] = 0;
        areas[grid[x][maxY - 1]] = 0;
    }

    for (int y = 0; y < maxY; ++y) {
        areas[grid[0][y]] = 0;
        areas[grid[maxX - 1][y]] = 0;
    }

    int maxArea = 0;
    for (int i = 1; i < points.size() + 1; ++i) {
        if (areas[i] > maxArea) {
            maxArea = areas[i];
        }
    }

    // for (int y = 0; y < maxY; ++y) {
    //     for (int x = 0; x < maxX; ++x) {
    //         cout << grid[x][y];
    //     }
    //     cout << endl;
    // }

    return maxArea;
}


int main() {
    vector<Point> points;
    readInput(points);
    cout << solve(points) << endl;
    return 0;
}