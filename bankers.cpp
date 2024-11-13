#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Process {
    int id;                // Process ID
    int arrivalTime;       // Arrival time of the process (not used here but can be extended)
    int burstTime;         // Total burst time of the process (not used here but can be extended)
    int remainingTime;     // Remaining time for the process (not used here but can be extended)
    int finishTime;        // Finish time
    int turnaroundTime;    // Turnaround time (Finish Time - Arrival Time)
    int waitingTime;       // Waiting time (Turnaround Time - Burst Time)
};

// Function to calculate Preemptive Priority Scheduling
bool isSafeState(vector<vector<int>>& allocation, vector<vector<int>>& max, vector<int>& available, int n, int m) {
    vector<int> work = available;
    vector<bool> finish(n, false);
    int completed = 0;

    while (completed < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canExecute = true;
                for (int j = 0; j < m; j++) {
                    if (max[i][j] - allocation[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }

                if (canExecute) {
                    found = true;
                    finish[i] = true;
                    completed++;

                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                }
            }
        }

        if (!found) {
            return false;
        }
    }

    return true;
}

int main() {
    int n = 5;  // Number of processes
    int m = 3;  // Number of resources

    // Hardcoded Allocation Matrix (n x m)
    vector<vector<int>> allocation = {
        {0, 1, 0},  // Process 0
        {2, 0, 0},  // Process 1
        {3, 0, 2},  // Process 2
        {2, 1, 1},  // Process 3
        {0, 0, 2}   // Process 4
    };

    // Hardcoded Maximum Matrix (n x m)
    vector<vector<int>> max = {
        {7, 5, 3},  // Process 0
        {3, 2, 2},  // Process 1
        {9, 0, 2},  // Process 2
        {2, 2, 2},  // Process 3
        {4, 3, 3}   // Process 4
    };

    // Hardcoded Available Resources (m)
    vector<int> available = {3, 3, 2};  // Available resources

    // Check if the system is in a safe state
    if (isSafeState(allocation, max, available, n, m)) {
        cout << "The system is in a safe state." << endl;
    } else {
        cout << "The system is not in a safe state." << endl;
    }

    return 0;  // Successful execution
}

/*
    Program Description:
    This C++ program implements the Banker's Algorithm to check if a system is in a safe state.
    The system checks whether a sequence of processes can execute without causing deadlock.
    
    Hardcoded values are used for the Allocation Matrix, Maximum Matrix, and Available Resources.

    FAQ Section:

    Q1: **What is Banker's Algorithm?**
    A1: The **Banker's Algorithm** is a resource allocation and deadlock avoidance algorithm. It ensures that a system remains in a safe state by checking if a sequence of processes can be executed without leading to a deadlock.

    Q2: **What is a safe state?**
    A2: A system is in a **safe state** if there exists a sequence of processes such that each process can obtain the required resources, execute, and release the resources without causing deadlock.

    Q3: **What is an unsafe state?**
    A3: A system is in an **unsafe state** if no such sequence of processes exists, which could potentially lead to deadlock.

    Q4: **What are the key matrices in the Banker's Algorithm?**
    A4: The key matrices are:
        - **Allocation Matrix**: Shows how many resources are allocated to each process.
        - **Maximum Matrix**: Shows the maximum resources each process may need.
        - **Available Matrix**: Shows the resources available in the system.

    Q5: **What happens if the system is not in a safe state?**
    A5: If the system is not in a safe state, it means that there is a potential for deadlock, as no sequence of processes can execute without leading to a resource allocation deadlock.

    Q6: **What is the main limitation of Banker's Algorithm?**
    A6: The **Banker's Algorithm** requires knowledge of the maximum resources each process will need in advance, which may not always be possible to predict.
*/
