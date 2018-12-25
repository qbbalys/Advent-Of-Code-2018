#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_set>

using namespace std;

static const long long GENERATION_COUNT = 50000000000;

struct TrieNode {
    bool found;
    bool exists;
    int fail;
    TrieNode() : found(false), exists(false), fail(0) {}
};

struct HistoryRecord {
    string pots;
    int firstPotIndex;

    HistoryRecord(string _pots, int _firstPotIndex) : pots(_pots), firstPotIndex(_firstPotIndex) {}
};

void dumpTrie(const vector<TrieNode> &trie) {
    for (int i = 0; i < trie.size(); ++i) {
        cout << i << ": exists[" << trie[i].exists << "] found[" << trie[i].found << "] fail: " << trie[i].fail << endl;  
    }
}
 
vector<TrieNode> buildTrie(const vector<string> &patterns) {
    vector<TrieNode> trie(pow(2,7));
    trie[1].exists = true;

    for (const string &pattern : patterns) {
        int nodeIndex = 1;
        for (const char c : pattern) {
            if (c == '#') {
                nodeIndex = nodeIndex * 2;
                trie[nodeIndex].exists = true;
            } else {
                nodeIndex = nodeIndex * 2 + 1;
                trie[nodeIndex].exists = true;
            }
        }
        trie[nodeIndex].found = true;
    }

    return trie;
}

void calcFails(vector<TrieNode> &trie) {
    trie[2].fail = 1;
    trie[3].fail = 1;

    for (int i = 2; i < trie.size(); ++i) {
        if (!trie[i].exists) continue;
        
        if (trie[2 * i].exists) {
            int failIndex = trie[i].fail;
            while (!trie[failIndex * 2].exists) {
                failIndex = trie[failIndex].fail;
            }
            trie[2 * i].fail = failIndex * 2;
        }

        if (trie[2 * i + 1].exists) {
            int failIndex = trie[i].fail;
            while (!trie[failIndex * 2 + 1].exists) {
                failIndex = trie[failIndex].fail;
            }
            trie[2 * i + 1].fail = failIndex * 2 + 1;
        }
    }
}

string ahoCorasick(const string &pots, const vector<TrieNode> &trie) {
    string nextGen(pots.size(), '.');
    int trieIndex = 1;

    for (int i = 0; i < pots.size(); ++i) {
        if (pots[i] == '#') {
            while (!trie[trieIndex * 2].exists) {
                trieIndex = trie[trieIndex].fail;
            }
            trieIndex = trieIndex * 2;
        } else {
            while (!trie[trieIndex * 2 + 1].exists) {
                trieIndex = trie[trieIndex].fail;
            }
            trieIndex = trieIndex * 2 + 1;
        }

        if (trie[trieIndex].found) {
           nextGen[i - 2] = '#';
        }
    }

    return nextGen;
}

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

void adjustRange(string &pots, long long &firstPotIndex) {
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

long long calcResult(const string &pots, long long firstPotIndex) {
    long long result = 0;
    long long potIndex = firstPotIndex;
    for (int i = 0; i < pots.size(); ++i, ++potIndex) {
        if (pots[i] == '#') result += potIndex;
    }
    return result;
}

void simulate(string &pots, long long &firstPotIndex, const vector<TrieNode> &trie) {
    unordered_set<string> uniqueGenerations;
    vector<HistoryRecord> history;

    adjustRange(pots, firstPotIndex);
    history.push_back(HistoryRecord(pots, firstPotIndex));
    bool unique = uniqueGenerations.insert(pots).second;

    while (unique) {
        pots = ahoCorasick(pots, trie);
        adjustRange(pots, firstPotIndex);
        history.push_back(HistoryRecord(pots, firstPotIndex));
        unique = uniqueGenerations.insert(pots).second;
    }

    firstPotIndex = firstPotIndex + (GENERATION_COUNT - history.size() + 1) * (firstPotIndex - history[history.size() - 2].firstPotIndex);
}

int main() {
    long long firstPotIndex = 0;
    string pots;
    vector<string> patterns;
    readInput(pots, patterns);
    vector <TrieNode> trie = buildTrie(patterns);
    calcFails(trie);
    // dumpTrie(trie);
    simulate(pots, firstPotIndex, trie);
    cout << calcResult(pots, firstPotIndex) << endl;
    return 0;
}