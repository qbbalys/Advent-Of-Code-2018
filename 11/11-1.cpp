#include <iostream>

using namespace std;

static const int GRID_SIZE = 300;

int calcPowerLevel(int x, int y, int serial) {
    int rackId = x + 10;
    int powerLevel = ((((rackId * y + serial) * rackId) % 1000) / 100) - 5;
    return powerLevel;
}

int main() {
    int grid[GRID_SIZE][GRID_SIZE];
    int serial, maxTotal, maxX, maxY;
    maxTotal = 0;
    cin >> serial;

    for (int y = 0; y < GRID_SIZE; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            grid[y][x] = calcPowerLevel(x, y, serial);
        }
    }

    for (int y = 0; y < GRID_SIZE - 2; ++y) {
        for (int x = 0; x < GRID_SIZE - 2; ++x) {
            int total = grid[y][x] + grid[y][x + 1] + grid[y][x + 2] +
                        grid[y + 1][x] + grid[y + 1][x + 1] + grid[y + 1][x + 2] +
                        grid[y + 2][x] + grid[y + 2][x + 1] + grid[y + 2][x + 2];

            if (total > maxTotal) {
                maxTotal = total;
                maxX = x;
                maxY = y;
            }
        }
    }
    
    cout << maxX << "," << maxY << endl;
    return 0;
}