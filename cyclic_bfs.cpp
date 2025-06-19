#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <iomanip>
#include <unordered_map>
#include <algorithm>

using namespace std;

const int N = 7;
vector<string> labels = {"A", "B", "C", "D", "E", "F", "G"};

void printMatrix(const vector<vector<int>>& matrix) {
    cout << "Adjacency Matrix:\n    ";
    for (int i = 0; i < N; ++i)
        cout << labels[i] << " ";
    cout << "\n";

    for (int i = 0; i < N; ++i) {
        cout << labels[i] << " | ";
        for (int j = 0; j < N; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

bool detectCycleBFS(const vector<vector<int>>& matrix, vector<int>& cycle) {
    vector<int> inDegree(N, 0);
    vector<bool> processed(N, false);

    // Step 1: Compute in-degrees
    for (int u = 0; u < N; ++u)
        for (int v = 0; v < N; ++v)
            if (matrix[u][v]) inDegree[v]++;

    queue<int> q;
    for (int i = 0; i < N; ++i)
        if (inDegree[i] == 0)
            q.push(i);

    int processedCount = 0;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        processed[node] = true;
        processedCount++;

        for (int v = 0; v < N; ++v) {
            if (matrix[node][v]) {
                inDegree[v]--;
                if (inDegree[v] == 0)
                    q.push(v);
            }
        }
    }

    // Step 2: If there's a cycle, reconstruct it
    if (processedCount != N) {
        vector<bool> visited(N, false);
        vector<int> parent(N, -1);
        for (int start = 0; start < N; ++start) {
            if (!processed[start]) {
                queue<int> q2;
                q2.push(start);
                visited[start] = true;

                while (!q2.empty()) {
                    int u = q2.front(); q2.pop();

                    for (int v = 0; v < N; ++v) {
                        if (matrix[u][v]) {
                            if (!visited[v]) {
                                visited[v] = true;
                                parent[v] = u;
                                q2.push(v);
                            } else if (v != parent[u]) {
                                // Cycle found
                                cycle.push_back(v);
                                int temp = u;
                                while (temp != v && temp != -1) {
                                    cycle.push_back(temp);
                                    temp = parent[temp];
                                }
                                cycle.push_back(v);
                                reverse(cycle.begin(), cycle.end());
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}

int main() {
    vector<vector<int>> matrix = {
        {0, 0, 1, 0, 0, 0, 0}, // A → C
        {0, 0, 0, 0, 0, 0, 0}, // B
        {0, 1, 0, 0, 1, 1, 1}, // C → B,E,F,G
        {1, 0, 0, 0, 0, 0, 0}, // D → A
        {1, 0, 0, 0, 0, 0, 0}, // E → A
        {0, 1, 0, 0, 0, 0, 0}, // F → B
        {0, 0, 0, 0, 0, 0, 0}  // G
    };

    printMatrix(matrix);

    vector<int> cycle;
    bool hasCycle = detectCycleBFS(matrix, cycle);

    cout << "\n";
    if (hasCycle && !cycle.empty()) {
        cout << "Cycle Detected (BFS): (";
        for (size_t i = 0; i < cycle.size(); ++i) {
            cout << labels[cycle[i]];
            if (i + 1 < cycle.size())
                cout << " → ";
        }
        cout << ")\n";
    } else {
        cout << "No cycle detected using BFS.\n";
    }

    return 0;
}
