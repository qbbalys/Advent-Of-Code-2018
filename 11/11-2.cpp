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
    int serial, maxTotal, maxX, maxY, maxSize;
    maxTotal = 0;
    cin >> serial;

    for (int y = 0; y < GRID_SIZE; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            int sum = calcPowerLevel(x, y, serial);
            if (y - 1 >= 0) sum += grid[y - 1][x];
            if (x - 1 >= 0) sum += grid[y][x - 1];
            if (x - 1 >= 0 && y - 1 >= 0) sum -= grid[y - 1][x - 1];
            grid[y][x] = sum;
        }
    }

    for (int n = 1; n <= GRID_SIZE; ++n) {
        for (int y = 0; y < GRID_SIZE - n + 1; ++y) {
            for (int x = 0; x < GRID_SIZE - n + 1; ++x) {
                int total = grid[y + n - 1][x + n - 1];
                if (y - 1 >= 0) total -= grid[y - 1][x + n - 1];
                if (x - 1 >= 0) total -= grid[y + n - 1][x - 1];
                if (x - 1 >= 0 && y - 1 >= 0) total += grid[y - 1][x - 1];

                if (total > maxTotal) {
                    maxTotal = total;
                    maxX = x;
                    maxY = y;
                    maxSize = n;
                }
            }
        }
    }
    
    cout << maxX << "," << maxY << "," << maxSize << endl;
    return 0;
}