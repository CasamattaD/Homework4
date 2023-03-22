#pragma once
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Digraph {
private:
    int V;
    vector<int>* adj;

public:
    Digraph(int V) {
        this->V = V;
        adj = new vector<int>[V];
    }

    ~Digraph() {
        delete[] adj;
    }

    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }

    void removeEdge(int v, int w) {
        adj[v].erase(remove(adj[v].begin(), adj[v].end(), w), adj[v].end());
    }

    bool isAcyclic() {
        vector<bool> visited(V, false);
        vector<bool> recStack(V, false);

        for (int i = 0; i < V; i++) {
            if (!visited[i] && isAcyclicUtil(i, visited, recStack)) {
                return false;
            }
        }

        return true;
    }

    bool isAcyclicUtil(int v, vector<bool>& visited, vector<bool>& recStack) {
        visited[v] = true;
        recStack[v] = true;

        for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
            if (!visited[*i] && isAcyclicUtil(*i, visited, recStack)) {
                return true;
            }
            else if (recStack[*i]) {
                return true;
            }
        }

        recStack[v] = false;

        return false;
    }

    void topologicalSort() {
        stack<int> Stack;
        vector<bool> visited(V, false);

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, Stack);
            }
        }

        while (!Stack.empty()) {
            cout << Stack.top() << " ";
            Stack.pop();
        }
    }

    void topologicalSortUtil(int v, vector<bool>& visited, stack<int>& Stack) {
        visited[v] = true;

        for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
            if (!visited[*i]) {
                topologicalSortUtil(*i, visited, Stack);
            }
        }

        Stack.push(v);
    }
};

int main() {
    vector<string> tasks;
    int num_tasks;

    cout << "How many tasks do you want to enter? ";
    cin >> num_tasks;

    for (int i = 0; i < num_tasks; i++) {
        string task;
        cout << "Enter task #" << i + 1 << ": ";
        // cin.getline(task, 50);
        tasks.push_back(task);
    }

    cout << "Here are your tasks:" << endl;
    for (string task : tasks) {
        cout << "- " << task << endl;
    }

    return 0;
}