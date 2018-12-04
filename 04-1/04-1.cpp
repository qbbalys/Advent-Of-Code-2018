#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Record {
    int Y, M, D, h, m, id;
    char event;

    Record(int _Y, int _M, int _D, int _h, int _m, int _id, char _event) :
        Y(_Y), M(_M), D(_D), h(_h), m(_m), id(_id), event(_event) {}
};

ostream& operator<<(ostream& os, const Record &r) {
    os << "[" << r.Y << "-" <<
       setfill('0') << setw(2) << r.M << "-" <<
       setfill('0') << setw(2) << r.D << " " <<
       setfill('0') << setw(2) << r.h << ":" <<
       setfill('0') << setw(2) << r.m << "] " << r.event << " #" << r.id;
    return os;
}

bool compareDates(const Record &a, const Record &b) {
    if (a.Y < b.Y) return true;
    if (a.Y > b.Y) return false;
    if (a.M < b.M) return true;
    if (a.M > b.M) return false;
    if (a.D < b.D) return true;
    if (a.D > b.D) return false;
    if (a.h < b.h) return true;
    if (a.h > b.h) return false;
    if (a.m < b.m) return true;
    return false;
}

void readInput(vector<Record> &records) {
    int Y, M, D, h, m, id;
    char c, e;
    string event;

    while (cin >> c >> Y >> c >> M >> c >> D >> h >> c >> m >> c >> event) {
        id = -1;
        e = 0;

        if (event == "Guard") {
            cin >> c >> id;
            e = 'b';
        } else if (event == "falls") {
            e = 's';
        } else {
            e = 'w';
        }

        cin.ignore(INT_MAX, '\n');

        records.push_back(Record(Y, M, D, h, m, id, e));
    }

    sort(records.begin(), records.end(), compareDates);

    int currentId = -1;
    for (Record &r : records) {
        if (r.id != -1) {
            currentId = r.id;
        } else {
            r.id = currentId;
        }
    }

    // for (const Record &r : records) {
    //     cout << r << endl;
    // }
}

int findSnorlax(const vector<Record> &records) {
    unordered_map<int, int> stats;

    int napStart = 0;
    for (const Record &r : records) {
        if (r.event == 's') {
            napStart = r.m;
        } else if (r.event == 'w') {
            int napTime = r.m - napStart;
            if (stats.find(r.id) == stats.end()) {
                stats[r.id] = napTime;
            } else {
                stats[r.id] += napTime;
            }
        }
    }

    int snorlaxId = -1;
    int longestNap = 0;

    for (auto i = stats.begin(); i != stats.end(); ++i) {
        if (i->second > longestNap) {
            longestNap = i->second;
            snorlaxId = i->first;
        }
    }

    return snorlaxId;
}

int findSleepestMinute(int id, const vector<Record> &records) {
    int histogram[60];
    memset(histogram, 0, sizeof(histogram));

    int napStart = 0;
    for (const Record &r : records) {
        if (r.id != id) continue;

        if (r.event == 's') {
            napStart = r.m;
        } else if (r.event == 'w') {
            for (int i = napStart; i < r.m; ++i) {
                histogram[i]++;
            }
        }
    }

    int topMinute = -1;
    int topValue = -1;

    for (int i = 0; i < 60; ++i) {
        if (histogram[i] > topValue) {
            topValue = histogram[i];
            topMinute = i;
        }
    }

    return topMinute;
}

int main() {
    vector<Record> records;
    readInput(records);
    int id = findSnorlax(records);
    int min = findSleepestMinute(id, records);
    cout << id * min << endl;
    return 0;
}