#include <iostream>
#include <vector>
#include <set>

using namespace std;

static const int GRAPH_SIZE = 'Z' - 'A' + 1;

struct Vertex {
    int degree;
    vector<int> edges;

    Vertex() : degree(0) {}

    bool used() const {
        return degree > 0 || !edges.empty();
    }
};

struct QueueCmp {
    Vertex *graph;
    QueueCmp(Vertex *_graph) : graph(_graph) {}

    bool operator()(int a, int b) const {
        if (graph[a].degree < graph[b].degree) return true;
        if (graph[a].degree > graph[b].degree) return false;
        return a < b;
    }
};

void dump(const Vertex graph[]) {
    for (int i = 0; i < GRAPH_SIZE; ++i) {
        if (!graph[i].used()) continue;
        cout << static_cast<char>(i + 'A') << " [" << graph[i].degree << "]: ";
        for (int v : graph[i].edges) {
            cout << static_cast<char>(v + 'A') << " ";
        }
        cout << endl;
    }
}

void readInput(Vertex graph[]) {
    string line;
    while (getline(cin, line)) {
        char a = line[5];
        char b = line[36];
        graph[a - 'A'].edges.push_back(b - 'A');
        graph[b - 'A'].degree++;
    }
}

string solve(Vertex graph[]) {
    set<int, QueueCmp> queue((QueueCmp(graph)));
    string solution;

    for (int i = 0; i < GRAPH_SIZE; ++i) {
        if (graph[i].used()) {
            queue.insert(i);
        }
    }

    while (!queue.empty()) {
        int current = *queue.begin();
        queue.erase(queue.begin());
        solution.push_back(static_cast<char>(current + 'A'));

        for (int v : graph[current].edges) {
            queue.erase(queue.find(v));
            graph[v].degree--;
            queue.insert(v);
        }
    }

    return solution;
}

int main() {
    Vertex graph[GRAPH_SIZE];
    readInput(graph);
    // dump(graph);
    cout << solve(graph) << endl;
    return 0;
}