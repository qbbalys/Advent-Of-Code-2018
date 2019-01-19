#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

static const char GROUND = '.';
static const char TREE = '|';
static const char YARD = '#';

struct Hash {
    size_t operator() (const vector<string> &map) const {
        size_t value = 0;
        for (const string &line : map) {
            value ^= hash<string>()(line);
        }
        return value;
    }
};

void readInput(vector<string> &map) {
    string line;

    while (cin >> line) {
        map.push_back(line);
    } 
}

void dumpMap(const vector<string> &map) {
    for (const string &line : map) {
        cout << line << endl;
    }
}

inline void updateCount(char c, int &ground, int &trees, int &yards) {
    switch (c) {
        case GROUND: ++ground; break;
        case TREE: ++trees; break;
        case YARD: ++yards; break;
        default: break;
    }
}

void countAdjacent(int &ground, int &trees, int &yards, int x, int y, const vector<string> &map) {
    ground = trees = yards = 0;

    if (x - 1 >= 0)                                  updateCount(map[y][x - 1], ground, trees, yards);
    if (x + 1 < map[y].size())                       updateCount(map[y][x + 1], ground, trees, yards);
    if (y - 1 >= 0)                                  updateCount(map[y - 1][x], ground, trees, yards);
    if (y + 1 < map.size())                          updateCount(map[y + 1][x], ground, trees, yards);
    if (x - 1 >= 0 && y - 1 >= 0)                    updateCount(map[y - 1][x - 1], ground, trees, yards);
    if (x + 1 < map[y].size() && y - 1 >= 0)         updateCount(map[y - 1][x + 1], ground, trees, yards);
    if (x + 1 < map[y].size() && y + 1 < map.size()) updateCount(map[y + 1][x + 1], ground, trees, yards);
    if (x - 1 >= 0 && y + 1 < map.size())            updateCount(map[y + 1][x - 1], ground, trees, yards);
}

bool operator==(const vector<string> &lhs, const vector<string> &rhs) {
    if (lhs.size() != rhs.size()) return false;

    for (int i = 0; i < lhs.size(); ++i) {
        if (lhs[i] != rhs[i]) return false;
    }

    return true;
}

void simulate(vector<string> &map) {
    int minute = 0;
    int repeatedIndex = 0;

    unordered_map<vector<string>, int, Hash> history;
    history[map] = minute;

    while (true) {
        ++minute;
        vector<string> nextState = map;

        for (int y = 0; y < map.size(); ++y) {
            for (int x = 0; x < map[y].size(); ++x) {

                int ground, trees, yards;
                countAdjacent(ground, trees, yards, x, y, map);

                switch (map[y][x]) {
                    case GROUND:
                        if (trees >= 3) nextState[y][x] = TREE;
                        break;
                    case TREE:
                        if (yards >= 3) nextState[y][x] = YARD;
                        break;
                    case YARD:
                        if (yards < 1 || trees < 1) nextState[y][x] = GROUND;
                        break;
                    default:
                        break;
                }
            }
        }

        map = nextState;
        auto insertResult = history.insert(make_pair(map, minute));
        if (!insertResult.second) {
            repeatedIndex = insertResult.first->second;
            break;
        }
    }

    int period = minute - repeatedIndex;
    int finalIndex = repeatedIndex + (1000000000 - repeatedIndex) % period;

    for (const auto &it : history) {
        if (it.second == finalIndex) {
            map = it.first;
        }
    }
}

int calcResourceValue(const vector<string> &map) {
    int treesTotal, yardsTotal;
    treesTotal = yardsTotal = 0;

    for (const string &line : map) {
        for (char c : line) {
            switch (c) {
                case TREE: ++treesTotal; break;
                case YARD: ++yardsTotal; break;
                default: break;
            }
        }
    }

    return treesTotal * yardsTotal;
}

int main() {
    vector<string> map;
    readInput(map);
    simulate(map);
    cout << calcResourceValue(map) << endl;
    return 0;
}