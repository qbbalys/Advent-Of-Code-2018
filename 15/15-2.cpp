#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <algorithm>
#include <exception>

using namespace std;

struct Point;
struct Unit;
struct DistanceMap;

static const int NOT_FOUND = -1;

struct Point {
    int x, y;

    Point(int _x, int _y) : x(_x), y(_y) {}

    static Point invalid() {
        return Point(INT_MAX, INT_MAX);
    }

    bool operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }

    bool operator<(const Point &other) const {
        if (y < other.y) return true;
        if (y > other.y) return false;
        return x < other.x;
    }
};

ostream& operator<<(ostream &os, const Point &p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

struct DistanceMap {
    static const int UNVISITED = -1;

    vector<vector<int>> distMap;

    DistanceMap(const Point &start, const vector<string> &map) : distMap(map.size()) {

        for (int i = 0; i < distMap.size(); ++i) {
            distMap[i] = vector<int>(map[i].size(), UNVISITED);
        }

        queue<Point> visited;
        distMap[start.y][start.x] = 0;
        visited.push(start);

        while (!visited.empty()) {
            Point curPoint = visited.front();
            visited.pop();
            int curDist = distMap[curPoint.y][curPoint.x];

            if (curPoint.y - 1 >= 0 && map[curPoint.y - 1][curPoint.x] == '.' && distMap[curPoint.y - 1][curPoint.x] == UNVISITED) {
                distMap[curPoint.y - 1][curPoint.x] = curDist + 1;
                visited.push(Point(curPoint.x, curPoint.y - 1));
            }

            if (curPoint.x - 1 >= 0 && map[curPoint.y][curPoint.x - 1] == '.' && distMap[curPoint.y][curPoint.x - 1] == UNVISITED) {
                distMap[curPoint.y][curPoint.x - 1] = curDist + 1;
                visited.push(Point(curPoint.x - 1, curPoint.y));
            }

            if (curPoint.x + 1 < map[curPoint.y].size() && map[curPoint.y][curPoint.x + 1] == '.' && distMap[curPoint.y][curPoint.x + 1] == UNVISITED) {
                distMap[curPoint.y][curPoint.x + 1] = curDist + 1;
                visited.push(Point(curPoint.x + 1, curPoint.y));
            }

            if (curPoint.y + 1 < map.size() && map[curPoint.y + 1][curPoint.x] == '.' && distMap[curPoint.y + 1][curPoint.x] == UNVISITED) {
                distMap[curPoint.y + 1][curPoint.x] = curDist + 1;
                visited.push(Point(curPoint.x, curPoint.y + 1));
            }
        }
    }

    void dump() const {
        for (const vector<int> &line : distMap) {
            for (int dist : line) {
                if (dist == UNVISITED)
                    cout << " . ";
                else
                    cout << setfill(' ') << setw(2) << dist << " ";
            }
            cout << endl;
        }
    }

    Point nearestAccessibleLocation(const vector<Point> &points) const {
        Point found = Point::invalid();

        for (const Point &p : points) {
            if (p.y < 0 || p.y >= distMap.size() || p.x < 0 || p.x >= distMap[p.y].size() || distMap[p.y][p.x] == UNVISITED)
                continue;

            if (found == Point::invalid()) {
                found = p;
            } else if (distMap[p.y][p.x] < distMap[found.y][found.x]) {
                found = p;
            } else if (distMap[p.y][p.x] == distMap[found.y][found.x] && p < found) {
                found = p;
            }
        }

        return found;
    }
};

struct Unit {
    static const int INITIAL_HP = 200;
    static const int ATTACK_POWER = 3;

    char type;
    int hp;
    Point pos;

    static bool isUnit(char c) {
        return c == 'E' || c == 'G';
    }

    Unit(char _type, int _x, int _y) : type(_type), pos(Point(_x, _y)), hp(INITIAL_HP) {}

    bool operator<(const Unit &other) const {
        return pos < other.pos;
    }

    vector<Point> locationsInRange() const {
        return {
            Point(pos.x, pos.y - 1),
            Point(pos.x - 1, pos.y),
            Point(pos.x + 1, pos.y),
            Point(pos.x, pos.y + 1)
        };
    }

    vector<Point> possibleTargetLocations(const vector<Unit> &units) {
        vector<Point> locations;
        
        for (const Unit &unit : units) {
            if (unit.type != type) {
                vector<Point> nearby = unit.locationsInRange();
                locations.insert(locations.end(), nearby.begin(), nearby.end());
            }
        }

        return locations;
    }

    bool isEnemyInRange(const Unit &other) const {
        if (type == other.type) return false;
        vector<Point> nearby = locationsInRange();
        return find(nearby.begin(), nearby.end(), other.pos) != nearby.end();
    }

    int enemyIndexInRange(const vector<Unit> &units) const {
        int enemyIndex = NOT_FOUND;

        for (int i = 0; i < units.size(); ++i) {
            Unit target = units[i];
            if (!isEnemyInRange(target)) continue;

            if (enemyIndex == NOT_FOUND) {
                enemyIndex = i;
            } else if (target.hp < units[enemyIndex].hp) {
                enemyIndex = i;
            } else if (target.hp == units[enemyIndex].hp && target.pos < units[enemyIndex].pos) {
                enemyIndex = i;
            }
        }

        return enemyIndex;
    }

    bool move(vector<string> &map, const vector<Unit> &units) {
        DistanceMap distances(pos, map);
        vector<Point> possibleLocations = possibleTargetLocations(units);
        if (possibleLocations.empty()) {
            return false;
        }

        Point targetLocation = distances.nearestAccessibleLocation(possibleLocations);
        if (targetLocation == Point::invalid()) {
            return true;
        }

        DistanceMap pathLengths(targetLocation, map);
        Point moveLocation = pathLengths.nearestAccessibleLocation(locationsInRange());
        
        if (moveLocation == Point::invalid()) {
            throw domain_error("Move calculation error");
        }
        
        map[pos.y][pos.x] = '.';
        map[moveLocation.y][moveLocation.x] = type;
        pos = moveLocation;

        return true;
    }
};

ostream& operator<<(ostream &os, const Unit &u) {
    os << u.type << " " << u.pos << " HP: " << u.hp;
    return os;
}

void dumpMap(const vector<string> &map, bool wide = false) {
    for (const string &line : map) {
        for (char c : line) {
            cout << (wide ? " " : "") << c << (wide ? " " : "");
        }
        cout << endl;
    }
}

void dumpUnits(const vector<Unit> &units) {
    for (const Unit &u : units) {
        cout << u << endl;
    }
}

void readInput(vector<string> &map, vector<Unit> &units) {
    string line;
    int y = 0;

    while (getline(cin, line)) {
        for (int x = 0; x < line.size(); ++x) {
            char c = line[x];
            if (Unit::isUnit(c)) {
                units.push_back(Unit(c, x, y));
            }
        }
        map.push_back(line);
        ++y;
    }
}

int simulate(vector<string> map, vector<Unit> units, int elfAttackPower) {
    for (int round = 0; true; ++round) {
        sort(units.begin(), units.end());

        for (int i = 0; i < units.size(); ++i) {
            Unit &curUnit = units[i];

            int enemyIndex = curUnit.enemyIndexInRange(units);
            if (enemyIndex == NOT_FOUND) {
                if (!curUnit.move(map, units)) {
                    int totalHp = 0;
                    for (const Unit &u : units) {
                        if (u.type != curUnit.type) throw domain_error("Oponents still alive");
                        totalHp += u.hp;
                    }
                    return round * totalHp;
                } 

                enemyIndex = curUnit.enemyIndexInRange(units);
                if (enemyIndex == NOT_FOUND) continue;
            }

            Unit &enemyUnit = units[enemyIndex];
            enemyUnit.hp -= curUnit.type == 'E' ? elfAttackPower : Unit::ATTACK_POWER;
            
            if (enemyUnit.hp <= 0) {
                if (enemyUnit.type == 'E') {
                    return -1;
                }

                map[enemyUnit.pos.y][enemyUnit.pos.x] = '.';
                units.erase(units.begin() + enemyIndex);

                if (enemyIndex < i) {
                    --i;
                }
            }
        }

        // cout << "Round " << round + 1 << ":\n";
        // dumpMap(map);
        // dumpUnits(units);
        // cout << endl;
    }
}

int solve(const vector<string> &map, const vector<Unit> &units) {
    int elfAttackPower = 4;
    int result = simulate(map, units, elfAttackPower);

    while (result < 0) {
        ++elfAttackPower;
        result = simulate(map, units, elfAttackPower);
    }

    return result;
}

int main() {
    vector<string> map;
    vector<Unit> units;

    readInput(map, units);
    cout << solve(map, units) << endl;

    return 0;
}