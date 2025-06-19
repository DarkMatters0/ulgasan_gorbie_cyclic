#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int N = 7;
char labels[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};

// Adjacency Matrix
int adj[N][N] = {
    {0, 0, 1, 0, 0, 0, 0}, // A
    {0, 0, 0, 0, 0, 0, 0}, // B
    {0, 1, 0, 0, 0, 1, 1}, // C
    {1, 0, 0, 0, 0, 0, 0}, // D
    {1, 0, 0, 0, 0, 0, 0}, // E
    {1, 0, 0, 0, 0, 0, 0}, // F
    {0, 0, 0, 0, 0, 0, 0}  // G
};

bool dfs(int v, vector<bool> &visited, vector<bool> &recStack, vector<int> &cycle) {
    visited[v] = recStack[v] = true;
    cycle.push_back(v);

    for (int i = 0; i < N; ++i) {
        if (adj[v][i]) {
            if (!visited[i] && dfs(i, visited, recStack, cycle)) return true;
            if (recStack[i]) {
                cycle.push_back(i); // Push start of cycle
                return true;
            }
        }
    }
    recStack[v] = false;
    cycle.pop_back();
    return false;
}

void detectCycleDFS() {
    vector<bool> visited(N, false), recStack(N, false);
    vector<int> cycle;
    bool hasCycle = false;

    for (int i = 0; i < N; ++i) {
        if (!visited[i] && dfs(i, visited, recStack, cycle)) {
            hasCycle = true;
            break;
        }
    }

    if (hasCycle) {
        cout << "Cycle Detected (DFS): ";
        for (int i = 0; i < cycle.size(); ++i)
            cout << labels[cycle[i]] << (i + 1 < cycle.size() ? " -> " : "\n");
    } else {
        cout << "No cycle detected using DFS.\n";
    }
}

int main() {
    cout << "Directed Graph (Adjacency Matrix):\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << adj[i][j] << " ";
        }
        cout << " <- " << labels[i] << "\n";
    }
    detectCycleDFS();
    return 0;
}
