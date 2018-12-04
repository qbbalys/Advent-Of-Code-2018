#include <iostream>
#include <vector>

using namespace std;

struct Rect {
    int id, x, y, w, h;

    Rect(int _id, int _x, int _y, int _w, int _h) : id(_id), x(_x), y(_y), w(_w), h(_h) {} 

    int maxX() const {
        return x + w;
    }

    int maxY() const {
        return y + h;
    }

    bool intersects(const Rect &other) const {
        if (maxX() <= other.x || x >= other.maxX() || maxY() <= other.y || y >= other.maxY())
            return false;
        return true;
    }
};

void readInput(vector<Rect> &rects) {
    int n, x, y, w, h;
    char c;
    
    while (cin >> c >> n >> c >> x >> c >> y >> c >> w >> c >> h) {
        // cout << n << ": " << x << ", " << y << " (" << w << ", " << h << ")\n";
        rects.push_back(Rect(n, x, y, w, h));
    }
}

void brut(const vector<Rect> &rects) {
    int maxX = 0, maxY = 0;
    for (const Rect &r : rects) {
        if (r.maxX() > maxX) maxX = r.maxX();
        if (r.maxY() > maxY) maxY = r.maxY();
    }

    int plane[maxX][maxY];
    memset(plane, 0, sizeof(plane));

    for (const Rect &r : rects) {
        for (int i = r.x; i < r.maxX(); ++i) {
            for (int j = r.y; j < r.maxY(); ++j) {
                plane[i][j]++;
            }
        }
    }

    int area = 0;

    for (int i = 0; i < maxX; ++i) {
        for (int j = 0; j < maxY; ++j) {
            if (plane[i][j] > 1) {
                area++;
            }
        }
    }

    cout << area << endl;
}

void brut2(const vector<Rect> &rects) {
    for (int i = 0; i < rects.size(); ++i) {
        bool overlaps = false;

        for (int j = 0; j < rects.size(); ++j) {
            if (i == j) continue;
            if (rects[i].intersects(rects[j])) {
                overlaps = true;
                break;
            }
        }
        if (!overlaps) {
            cout << rects[i].id << endl;
        }
    }
}

int main() {
    vector<Rect> rects;
    readInput(rects);
    brut2(rects);

    return 0;
}