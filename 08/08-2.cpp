#include <iostream>

using namespace std;

int solve() {
    int childCount, metaCount, value = 0;
    cin >> childCount >> metaCount;

    int childValues[childCount];

    for (int i = 0; i < childCount; ++i) {
        childValues[i] = solve();
    }

    for (int i = 0; i < metaCount; ++i) {
        int metaValue;
        cin >> metaValue;

        if (childCount == 0) {
            value += metaValue;
        } else {
            int childIndex = metaValue - 1;
            if (childIndex >= 0 && childIndex < childCount) {
                value += childValues[childIndex];
            }
        }
    }

    return value;
}

int main() {
    cout << solve() << endl;
    return 0;
}