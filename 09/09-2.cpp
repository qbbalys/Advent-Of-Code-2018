#include <iostream>
#include <vector>

using namespace std;

long long solve(int playerCount, int lastMarble) {
    int currentPlayer = 0, currentMarble = 0;
    vector<int> circle = {0};
    long long scores[playerCount];
    memset(scores, 0, sizeof(scores));

    for (int marble = 1; marble <= lastMarble; ++marble) {
        if (marble % 23 == 0) {
            scores[currentPlayer] += marble;
            currentMarble -= 7;
            if (currentMarble < 0) {
                currentMarble += circle.size();
            }
            scores[currentPlayer] += circle[currentMarble];
            circle.erase(circle.begin() + currentMarble);
            currentMarble %= circle.size();
        } else {
            currentMarble += 2;
            if (currentMarble > circle.size()) {
                currentMarble -= circle.size();
            }
            circle.insert(circle.begin() + currentMarble, marble);
        }

        // cout << "[" << currentPlayer + 1 << "] ";
        // for (int m : circle) cout << m << " ";
        // cout << endl;

        ++currentPlayer;
        currentPlayer %= playerCount;

        cout << "\r" << marble;
    }

    cout << endl;

    long long maxScore = 0;
    for (long long score : scores) {
        maxScore = max(maxScore, score);
    }
    return maxScore;
}

int main() {
    int playerCount, lastMarble;

    while (cin.good()) {
        cin >> playerCount;
        cin.ignore(30);
        cin >> lastMarble;
        cin.ignore(INT_MAX, '\n');
        cout << solve(playerCount, lastMarble * 100) << endl;
    }
    
    return 0;
}