#include <iostream>

using namespace std;

int solve() {
    int childCount, metaCount, sum = 0;
    cin >> childCount >> metaCount;

    for (int i = 0; i < childCount; ++i) {
        sum += solve();
    }

    for (int i = 0; i < metaCount; ++i) {
        int metaValue;
        cin >> metaValue;
        sum += metaValue;
    }

    return sum;
}

int main() {
    cout << solve() << endl;
    return 0;
}