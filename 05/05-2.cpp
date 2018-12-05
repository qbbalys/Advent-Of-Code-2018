#include <iostream>
#include <cctype>

using namespace std;

bool reacts(char a, char b) {
    if (isupper(a)) {
        return tolower(a) == b;
    } else {
        return toupper(a) == b;
    }
}

string filterUnits(char lowerUnit, const string &seq) {
    string filtered;
    for (char c : seq) {
        if (tolower(c) != lowerUnit) {
            filtered.push_back(c);
        }
    }
    return filtered;
}

int reduce(const string &seq) {
    string reduced;

    for (char c : seq) {
        if (reduced.size() > 0 && reacts(reduced.back(), c)) {
            reduced.pop_back();
        } else {
            reduced.push_back(c);
        }
    }

    return reduced.size();
}

int solve(const string &seq) {
    int minSize = INT_MAX;

    for (char c = 'a'; c <= 'z'; ++c) {
        string filtered = filterUnits(c, seq);
        int reducedSize = reduce(filtered);
        if (reducedSize < minSize) {
            minSize = reducedSize;
        }
    }

    return minSize;
}

int main() {
    char c;
    string seq;
    cin >> seq;

    cout << solve(seq) << endl;

    return 0;
}