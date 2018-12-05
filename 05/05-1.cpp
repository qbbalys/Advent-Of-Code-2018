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

int main() {
    char c;
    string seq;

    while (cin >> c) {
        if (seq.size() > 0 && reacts(seq.back(), c)) {
            seq.pop_back();
        } else {
            seq.push_back(c);
        }
    }

    cout << seq.size() << endl;

    return 0;
}