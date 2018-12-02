#include <iostream>
#include <vector>

using namespace std;

int main() {
    string code;
    vector<string> codes;

    while (cin >> code) {
        codes.push_back(code);
    }

    for (int i = 0; i < codes.size(); ++i) {
        string codeA = codes[i];
        for (int j = 0; j < codes.size(); ++j) {
            if (i == j) continue;
            string codeB = codes[j];
            if (codeA.size() != codeB.size()) continue;

            int diffIndex = -1;
            for (int k = 0; k < codeA.size(); ++k) {
                if (codeA[k] != codeB[k]) {
                    if (diffIndex < 0) {
                        diffIndex = k;
                    } else {
                        diffIndex = -1;
                        break;
                    }
                }
            }

            if (diffIndex >= 0) {
                cout << codeA.erase(diffIndex, 1) << endl;
                return 0;
            } 
        }
    }

    return 0;
}