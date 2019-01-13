#include <iostream>
#include <vector>

using namespace std;

static const char SAND = '.';
static const char CLAY = '#';
static const char FLOW = '|';
static const char WATER = '~';

struct Range2D {
    int xPos, xLen, yPos, yLen;
    Range2D() : xPos(0), xLen(0), yPos(0), yLen(0) {}
    Range2D(int _xPos, int _xLen, int _yPos, int _yLen) : xPos(_xPos), xLen(_xLen), yPos(_yPos), yLen(_yLen) {}
};

ostream& operator<<(ostream &os, const Range2D &range) {
    os << "x: [" << range.xPos << ", " << range.xLen << "] y: [" << range.yPos << ", " << range.yLen << "]";
    return os; 
}

void readInput(vector<Range2D> &blocks, int &mapWidth, int &mapHeight, int &springX) {
    char firstCoord;
    int xStart, xEnd, yStart, yEnd, minX, minY, maxX, maxY;
    minX = minY = INT_MAX;
    maxX = maxY = 0;

    while(cin >> firstCoord) {
        cin.ignore(1); // "="

        if (firstCoord == 'x') {
            cin >> xStart;
            xEnd = xStart;
            cin.ignore(4); // ", y="
            cin >> yStart;
            cin.ignore(2); // ".."
            cin >> yEnd;
        } else {
            cin >> yStart;
            yEnd = yStart;
            cin.ignore(4); // ", x="
            cin >> xStart;
            cin.ignore(2); // ".."
            cin >> xEnd;
        }

        cin.ignore(INT_MAX, '\n');

        minX = min(minX, xStart);
        maxX = max(maxX, xEnd);
        minY = min(minY, yStart);
        maxY = max(maxY, yEnd);
        blocks.push_back(Range2D(xStart, xEnd - xStart + 1, yStart, yEnd - yStart + 1));
    }

    mapWidth = maxX - minX + 3;
    mapHeight = maxY - minY + 1;
    springX = 500 - minX + 1;

    for (Range2D &block : blocks) {
        block.xPos -= (minX - 1);
        block.yPos -= minY;
    }

    // cout << "x: " << minX << " " << maxX << " y: " << minY << " " << maxY << endl;
}

void initMap(vector<string> &map, const vector<Range2D> &blocks, int mapWidth, int mapHeight) {
    map.resize(mapHeight);
    
    for (string &row : map) {
        row = string(mapWidth, SAND);
    }

    for (const Range2D &block : blocks) {
        for (int y = 0; y < block.yLen; ++y) {
            for (int x = 0; x < block.xLen; ++x) {
                map[block.yPos + y][block.xPos + x] = CLAY;
            }
        }
    }
}

void dumpMap(const vector<string> &map) {
    for (const string &row : map) {
        cout << row << endl;
    }
}

void markAdjacentFlow(int x, int y, vector<string> &map) {
    map[y][x] = FLOW;
    int curX = x - 1;

    while (curX >= 0 && map[y][curX] == WATER) {
        map[y][curX--] = FLOW;
    }

    curX = x + 1;
    while (curX < map[y].size() && map[y][curX] == WATER) {
        map[y][curX++] = FLOW;
    }
}

bool dfs(int x, int y, vector<string> &map) {
    if (y + 1 == map.size() || map[y + 1][x] == FLOW) {
        map[y][x] = FLOW;
        return true; // bottom reached
    }

    map[y][x] = WATER;
    bool reachedBottom = false;

    if (map[y + 1][x] == SAND) {
        reachedBottom = dfs(x, y + 1, map);
    }

    if (x - 1 >= 0 && map[y][x - 1] == SAND && (map[y + 1][x - 1] == CLAY || map[y + 1][x - 1] == WATER || map[y + 1][x] == CLAY)) {
        reachedBottom |= dfs(x - 1, y, map);
    }

    if (x + 1 < map[y].size() && map[y][x + 1] == SAND && (map[y + 1][x + 1] == CLAY || map[y + 1][x + 1] == WATER || map[y + 1][x] == CLAY)) {
        reachedBottom |= dfs(x + 1, y, map);
    }

    if (reachedBottom) {
        markAdjacentFlow(x, y, map);
    }

    return reachedBottom;
}

int totalWet(const vector<string> &map) {
    int sum = 0;

    for (const string &line : map) {
        for (char c : line) {
            if (c == WATER || c == FLOW) ++sum;
        }
    }

    return sum;
}

int totalWater(const vector<string> &map) {
    int sum = 0;

    for (const string &line : map) {
        for (char c : line) {
            if (c == WATER) ++sum;
        }
    }

    return sum;
}

int main() {
    vector<Range2D> blocks;
    int mapWidth, mapHeight, springX;
    readInput(blocks, mapWidth, mapHeight, springX);

    vector<string> map;
    initMap(map, blocks, mapWidth, mapHeight);
    dfs(springX, 0, map);
    // dumpMap(map);
    // cout << totalWet(map) << endl;
    cout << totalWater(map) << endl;

    return 0;
}