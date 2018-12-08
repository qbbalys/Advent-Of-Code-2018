#include <iostream>
#include <vector>
#include <set>

using namespace std;

static const int GRAPH_SIZE = 'Z' - 'A' + 1;
static const int WORKERS = 5;
static const int TASK_TIME = 60;

struct Vertex {
    int degree;
    vector<int> edges;
    vector<int> ancestors;

    Vertex() : degree(0) {}

    bool used() const {
        return degree > 0 || !edges.empty();
    }
};

struct TaskCmp {
    Vertex *graph;
    TaskCmp(Vertex *_graph) : graph(_graph) {}

    bool operator()(int a, int b) const {
        if (graph[a].degree < graph[b].degree) return true;
        if (graph[a].degree > graph[b].degree) return false;
        return a < b;
    }
};

struct WorkerCmp {
    int *workerTimes;
    WorkerCmp(int *_workerTimes) : workerTimes(_workerTimes) {}

    bool operator()(int a, int b) const {
        return workerTimes[a] < workerTimes[b];
    }
};

void dump(const Vertex graph[]) {
    for (int i = 0; i < GRAPH_SIZE; ++i) {
        if (!graph[i].used()) continue;
        cout << static_cast<char>(i + 'A') << " [" << graph[i].degree << "]: ";
        for (int v : graph[i].ancestors) {
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
        graph[b - 'A'].ancestors.push_back(a - 'A');
    }
}

int solve(Vertex graph[]) {
    set<int, TaskCmp> tasksQueue((TaskCmp(graph)));
    
    for (int i = 0; i < GRAPH_SIZE; ++i) {
        if (graph[i].used()) {
            tasksQueue.insert(i);
        }
    }

    int workerTimes[WORKERS];
    memset(workerTimes, 0, sizeof(workerTimes));

    int taskEndTimes[tasksQueue.size()];
    memset(taskEndTimes, 0, sizeof(taskEndTimes));

    multiset<int, WorkerCmp> workersQueue((WorkerCmp(workerTimes)));
    for (int i = 0; i < WORKERS; ++i) {
        workersQueue.insert(i);
    }

    int endTime = 0;

    while (!tasksQueue.empty()) {
        vector<int> availableTasks;

        for (int task : tasksQueue) {
            if (graph[task].degree > 0) break;
            availableTasks.push_back(task);
        }

        for (int task : availableTasks) {
            int lastAncestorEndTime = 0;
            
            for (int ancestor : graph[task].ancestors) {
                lastAncestorEndTime = max(lastAncestorEndTime, taskEndTimes[ancestor]);
            }

            int freeWorker = *workersQueue.begin();
            workersQueue.erase(workersQueue.begin());

            int taskEndTime = max(lastAncestorEndTime, workerTimes[freeWorker]) + task + TASK_TIME + 1;
            taskEndTimes[task] = taskEndTime;
            workerTimes[freeWorker] = taskEndTime;
            endTime = max(endTime, taskEndTime);

            workersQueue.insert(freeWorker);
            tasksQueue.erase(task);

            cout << static_cast<char>(task + 'A') << " w " << freeWorker << ": " << taskEndTime << endl;
        }

        for (int task : availableTasks) {
            for (int v : graph[task].edges) {
                tasksQueue.erase(v);
                graph[v].degree--;
                tasksQueue.insert(v);
            }
        }
    }

    return endTime;
}

int main() {
    Vertex graph[GRAPH_SIZE];
    readInput(graph);
    // dump(graph);
    cout << solve(graph) << endl;
    
    return 0;
}