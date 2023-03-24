#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

class Digraph {
private:
    int V;
    vector<int>* adj;

public:
    // Constructor
    Digraph(int V) {
        this->V = V;
        adj = new vector<int>[V];
    }

    // Destructor
    ~Digraph() {
        delete[] adj;
    }

    // Add edge to digraph
    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }

    // Remove edge from Digraph
    void removeEdge(int v, int w) {
        adj[v].erase(remove(adj[v].begin(), adj[v].end(), w), adj[v].end());
    }

    // Check if graph has any cycles
    bool isAcyclic() {
        vector<bool> prev(V, false);
        vector<bool> recStack(V, false);

        for (int i = 0; i < V; i++) {
            if (!prev[i] && isAcyclicUtil(i, prev, recStack)) {
                return false;
            }
        }

        return true;
    }

    // Recursive check if graph has any cycles
    bool isAcyclicUtil(int v, vector<bool>& prev, vector<bool>& recStack) {
        prev[v] = true;
        recStack[v] = true;

        for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
            if (!prev[*i] && isAcyclicUtil(*i, prev, recStack)) {
                return true;
            }
            else if (recStack[*i]) {
                return true;
            }
        }

        recStack[v] = false;

        return false;
    }

    // Sort the tasks according to order relations
    void topologicalSort(vector<string> tasks) {
        stack<int> Stack;
        vector<bool> prev(V, false);

        for (int i = 0; i < V; i++) {
            if (!prev[i]) {
                topologicalSortUtil(i, prev, Stack);
            }
        }

        while (!Stack.empty()) {
            cout << Stack.top() + 1 << " " << tasks[Stack.top()] << endl;
            Stack.pop();
        }
    }

    // Recursive function to sort tasks according to order relations
    void topologicalSortUtil(int v, vector<bool>& prev, stack<int>& Stack) {
        prev[v] = true;

        for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
            if (!prev[*i]) {
                topologicalSortUtil(*i, prev, Stack);
            }
        }

        Stack.push(v);
    }
};

int main() {
    const int max = 10;
    vector<string> tasks;
    int numTasks = 0;
    int numRelation = 0;

    cout << "Enter up to " << max << " tasks. Press Enter after each task or leave blank and press when all tasks have been entered." << endl;

    // Keep prompting the user to enter tasks until the maximum number of tasks is reached or the user enters an empty task
    while (numTasks < max) {
        string task;
        getline(cin, task);

        if (task.empty()) {
            break;
        }

        tasks.push_back(task);
        numTasks++;
    }

    Digraph graph(numTasks);
    cout << "Specify Order Relations: Press Enter after each task or ENTER '0' to complete order relations." << endl;

    // Get order relations and add to graph accordingly
    while (numRelation < 100){
        int taskNum = 0;
        int precTask = 0;
        cout << "Enter Task Number: ";
        cin >> taskNum;
        if (taskNum == 0)
        {
            break;
        }
        cout << "Enter Task " << taskNum << " must precede: ";
        cin >> precTask;

        graph.addEdge(taskNum - 1, precTask - 1);

        numRelation++;
    }

    graph.topologicalSort(tasks);

    return 0;
}