#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Point {
    int x, y, dx, dy;
    Point(int _x, int _y, int _dx, int _dy) : x(_x), y(_y), dx(_dx), dy(_dy) {}
};

void readInput(vector<Point> &points) {
    int x, y, dx, dy;

    while (cin.good()) {
        cin.ignore(10);
        cin >> x;
        cin.ignore(1);
        cin >> y;
        cin.ignore(12);
        cin >> dx;
        cin.ignore(1);
        cin >> dy;
        cin.ignore(INT_MAX, '\n');
        points.push_back(Point(x, y, dx, dy)); 
    }
}

void adjustPoints(vector<Point> &points, int &w, int &h) {
    int minX, maxX, minY, maxY;
    minX = minY = INT_MAX;
    maxX = maxY = 0;

    for (const Point &p : points) {
        minX = min(minX, p.x);
        maxX = max(maxX, p.x);
        minY = min(minY, p.y);
        maxY = max(maxY, p.y);
    }

    for (Point &p : points) {
        p.x += -minX;
        p.y += -minY;
    }
    
    w = maxX - minX + 1;
    h = maxY - minY + 1;
}

void movePoints(vector<Point> &points, bool forward) {
    for (Point &p : points) {
        p.x += forward ? p.dx : -p.dx;
        p.y += forward ? p.dy : -p.dy;
    }
}

void printBitmap(const vector<Point> &points, int w, int h) {
    bool bitmap[h][w];
    memset(bitmap, 0, sizeof(bitmap));

    fstream fs("img.pbm", fstream::out);
    fs << "P1\n" << w << " " << h << endl;

    for (const Point &p : points) {
        bitmap[p.y][p.x] = true;
    }

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            fs << static_cast<int>(bitmap[i][j]) << " ";
        }
        fs << endl;
    }

    fs.close();
} 

int main() {
    vector<Point> points;
    int w, h, lastW, i;
    lastW = INT_MAX;
    i = -1;

    readInput(points);
    adjustPoints(points, w, h);

    while (lastW > w) {
        ++i;
        lastW = w;
        movePoints(points, true);
        adjustPoints(points, w, h);
    }

    movePoints(points, false);
    adjustPoints(points, w, h);
    printBitmap(points, w, h);
    cout << i << endl;
    return 0;
}