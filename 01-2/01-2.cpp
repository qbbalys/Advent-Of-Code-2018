#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
    vector<int> changes;
    unordered_set<int> sums = {0};
    auto result = make_pair(sums.end(), false);
    int i = 0, n = 0, sum = 0;

    while (cin >> n) {
        changes.push_back(n);
    }

    do {
        sum += changes[i];
        i = (i + 1) % changes.size();
        result = sums.insert(sum);
    } while (result.second);

    cout << *(result.first) << endl;

    return 0;
}