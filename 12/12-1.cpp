#include <iostream>
#include <vector>

using namespace std;

static const int GENERATION_COUNT = 20;

void readInput(string &pots, vector<string> &patterns) {
    cin.ignore(15);
    cin >> pots;
    cin.ignore(INT_MAX, '\n');
    cin.ignore(INT_MAX, '\n');

    string line;
    while (getline(cin, line)) {
        if (line[9] == '#') {
            patterns.push_back(line.substr(0, 5));
        }
    }
}

void adjustRange(string &pots, int &firstPotIndex) {
    size_t firstPlantIndex = pots.find_first_of('#');
    
    if (firstPlantIndex == string::npos) {
        pots = ".....";
        return;
    }

    if (firstPlantIndex < 5) {
        pots.insert(0, string(5 - firstPlantIndex, '.'));
        firstPotIndex -= 5 - firstPlantIndex;
    }

    if (firstPlantIndex > 5) {
        pots.erase(0, firstPlantIndex - 5);
        firstPotIndex += firstPlantIndex - 5;
    }

    size_t lastPlantIndex = pots.find_last_of('#');

    if (pots.size() - 1 - lastPlantIndex < 5) {
        pots.append(string(5 - (pots.size() - 1 - lastPlantIndex), '.'));
    }

    if (pots.size() - 1 - lastPlantIndex > 5) {
        pots.erase(lastPlantIndex + 6, pots.size() - (lastPlantIndex + 6));
    }
}

void simulate(string &pots, int &firstPotIndex, const vector<string> &patterns) {
    for (int i = 0; i < GENERATION_COUNT; ++i) {
        adjustRange(pots, firstPotIndex);
        // cout << pots << endl;
        string nextGen(pots.size(), '.');

        for (const string &pattern : patterns) {
            size_t foundAt = pots.find(pattern);
            while (foundAt != string::npos) {
                nextGen[foundAt + 2] = '#';
                foundAt = pots.find(pattern, foundAt + 1);
            }
        }
        pots = nextGen;
    }

    adjustRange(pots, firstPotIndex);
    // cout << pots << endl;
}

int calcResult(const string &pots, int firstPotIndex) {
    int result = 0;
    int potIndex = firstPotIndex;
    for (int i = 0; i < pots.size(); ++i, ++potIndex) {
        if (pots[i] == '#') result += potIndex;
    }
    return result;
}

int main() {
    int firstPotIndex = 0;
    string pots;
    vector<string> patterns;
    readInput(pots, patterns);
    simulate(pots, firstPotIndex, patterns);
    cout << calcResult(pots, firstPotIndex) << endl;
    return 0;
}