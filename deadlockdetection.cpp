#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class DeadlockDetection {
private:
    int n; // Number of processes
    vector<vector<int>> waitForGraph; // Adjacency matrix for the wait-for graph
    vector<bool> visited; // Visited array for DFS
    vector<bool> inStack; // Keeps track of nodes in the current DFS path

public:
    // Constructor to initialize the graph
    DeadlockDetection(int processes) : n(processes), waitForGraph(processes, vector<int>(processes, 0)) {}

    // Function to add a waiting edge in the graph
    void addWaitForEdge(int i, int j) {
        waitForGraph[i][j] = 1; // Process i is waiting for resource held by process j
    }

    // Function to detect cycles using DFS
    bool detectCycleUtil(int v) {
        // Mark the current node as visited and part of the current DFS path
        visited[v] = true;
        inStack[v] = true;

        // Recur for all the adjacent nodes (processes waiting for resources)
        for (int i = 0; i < n; i++) {
            if (waitForGraph[v][i] == 1) {
                if (!visited[i] && detectCycleUtil(i)) {
                    return true;
                } else if (inStack[i]) {
                    return true; // Cycle detected
                }
            }
        }

        // Remove the node from the current DFS path and mark it as processed
        inStack[v] = false;
        return false;
    }

    // Function to check for deadlock (cycle detection in the wait-for graph)
    bool isDeadlocked() {
        visited.assign(n, false); // Reset visited array
        inStack.assign(n, false); // Reset inStack array

        // Run DFS from every process
        for (int i = 0; i < n; i++) {
            if (!visited[i] && detectCycleUtil(i)) {
                return true; // Deadlock detected
            }
        }

        return false; // No cycle detected, no deadlock
    }
};

int main() {
    int n, m;

    // Number of processes and resources (Hardcoded for simplicity)
    n = 4; // Number of processes
    m = 3; // Number of resources (not used in this particular approach, as it's based on processes)

    DeadlockDetection dd(n);

    // Hardcoded Wait-For Graph: process i is waiting for resource held by process j
    dd.addWaitForEdge(0, 1); // Process 0 is waiting for Process 1
    dd.addWaitForEdge(1, 2); // Process 1 is waiting for Process 2
    dd.addWaitForEdge(2, 0); // Process 2 is waiting for Process 0 (forming a cycle)

    // Check if the system is in a deadlock state
    if (dd.isDeadlocked()) {
        cout << "Deadlock detected!" << endl;
    } else {
        cout << "No deadlock detected." << endl;
    }

    return 0;
}

/*
    Program Description:
    This C++ program implements the **Deadlock Detection Algorithm** using a **Wait-For Graph**.
    The program builds the graph where each process is represented by a node. A directed edge from 
    process `i` to process `j` indicates that process `i` is waiting for a resource held by process `j`.
    The algorithm then performs a **Cycle Detection** in the graph using DFS. If a cycle is found, 
    it indicates that the system is in a **deadlock** state.
    
    FAQ Section:

    Q1: **What is a Wait-For Graph?**
    A1: A **Wait-For Graph** is a directed graph where each process is represented by a node. If a process `i` is waiting for a resource held by process `j`, an edge is drawn from `i` to `j`.

    Q2: **How is Deadlock detected using the Wait-For Graph?**
    A2: Deadlock is detected by checking for **cycles** in the Wait-For Graph. If there is a cycle, it indicates that the processes in that cycle are deadlocked.

    Q3: **How does the algorithm work?**
    A3: The algorithm uses **Depth-First Search (DFS)** to explore the graph. During the DFS, if a process is found to be part of the current path and revisited, it means there is a cycle, indicating a deadlock.

    Q4: **What happens when no cycle is found?**
    A4: If no cycle is found during the DFS, the system is not in a deadlock state, meaning all processes can eventually complete without waiting indefinitely.

    Q5: **How does the algorithm handle multiple processes?**
    A5: The algorithm checks all processes to see if a cycle exists starting from each process. If a cycle is found, the system is in a deadlock state.

    Q6: **Can this approach be extended for more resources?**
    A6: Yes, this approach works for any number of resources, as long as the system's state is represented in terms of which processes are holding which resources and which processes are waiting for them.
*/
