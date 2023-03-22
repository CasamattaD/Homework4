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

    void topologicalSort(vector<string> tasks) {
        stack<int> Stack;
        vector<bool> visited(V, false);

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, Stack);
            }
        }

        while (!Stack.empty()) {
            cout << Stack.top() << " " << tasks[Stack.top()] << endl;
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

    // Print out the tasks in the array
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

        graph.addEdge(taskNum, precTask);

        numRelation++;
    }


    graph.topologicalSort(tasks);


    return 0;
}