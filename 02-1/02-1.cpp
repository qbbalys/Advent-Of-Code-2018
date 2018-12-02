#include <iostream>

using namespace std;

int main() {
    int histogram['z' - 'a' + 1];
    string code;
    bool has2, has3;
    int count2 = 0, count3 = 0;

    while (cin >> code) {
        has2 = has3 = false;
        memset(histogram, 0, sizeof(histogram));

        for (const char a : code) {
            histogram[a - 'a']++;
        }

        for (const int count : histogram) {
            if (count == 2) has2 = true;
            if (count == 3) has3 = true;
        }

        if (has2) count2++;
        if (has3) count3++;
    }

    cout << count2 * count3 << endl;

    return 0;
}