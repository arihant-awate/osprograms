#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Process {
    int id;                // Process ID
    int arrivalTime;       // Arrival time of the process
    int burstTime;         // Burst time of the process (time required for execution)
    int remainingTime;     // Remaining time for preemptive scheduling
    int priority;          // Priority of the process
    int finishTime;        // Finish time
    int turnaroundTime;    // Turnaround time (Finish Time - Arrival Time)
    int waitingTime;       // Waiting time (Turnaround Time - Burst Time)
};

// Function to calculate Preemptive Priority Scheduling
void calculatePreemptivePriorityScheduling(vector<Process>& processes) {
    int currentTime = 0;
    int completed = 0;
    int n = processes.size();
    
    // Initialize remaining time to burst time
    for (int i = 0; i < n; ++i) {
        processes[i].remainingTime = processes[i].burstTime;
    }

    while (completed < n) {
        int idx = -1;
        int highestPriority = INT_MAX;

        // Find the process with the highest priority (lowest priority number)
        // and has arrived and is not completed
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (processes[i].priority < highestPriority) {
                    highestPriority = processes[i].priority;
                    idx = i;
                }
            }
        }

        // If no process is found, move time forward
        if (idx == -1) {
            ++currentTime;
            continue;
        }

        // Process the selected process for 1 unit of time
        processes[idx].remainingTime--;

        // If this is the last unit of time for the process, update its finish time, turnaround time, and waiting time
        if (processes[idx].remainingTime == 0) {
            processes[idx].finishTime = currentTime + 1;
            processes[idx].turnaroundTime = processes[idx].finishTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
            completed++;
        }

        // Update current time
        currentTime++;
    }
}

// Function to print the results in a tabular format
void printTable(const vector<Process>& processes) {
    cout << "Process\tArrival Time\tBurst Time\tPriority\tFinish Time\tTurnaround Time\tWaiting Time\n";
    for (const auto& p : processes) {
        cout << p.id << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t" 
             << p.priority << "\t\t" << p.finishTime << "\t\t" << p.turnaroundTime << "\t\t" 
             << p.waitingTime << "\n";
    }
}

int main() {
    // Initial process data (id, arrival time, burst time, priority)
    vector<Process> processes = {
        {1, 0, 6, 0, 2, 0, 0, 0},
        {2, 1, 8, 0, 1, 0, 0, 0},
        {3, 2, 7, 0, 3, 0, 0, 0},
        {4, 3, 3, 0, 4, 0, 0, 0},
        {5, 4, 4, 0, 2, 0, 0, 0}
    };

    // Calculate times for Preemptive Priority Scheduling
    cout << "Preemptive Priority Scheduling:\n";
    calculatePreemptivePriorityScheduling(processes);
    printTable(processes);

    return 0;  // Successful execution
}

/*
    Program Description:
    This C++ program implements the Preemptive Priority Scheduling algorithm, where processes are executed 
    based on their priority. The process with the highest priority (smallest priority number) is selected for 
    execution next. If a new process arrives with a higher priority, it preempts the currently running process.
    
    1. **Preemptive Priority Scheduling**:
        - The process with the highest priority (smallest priority number) is executed first.
        - If a new process arrives with a higher priority than the currently running process, 
          the current process is preempted and the new process starts executing.

    FAQ Section:

    Q1: **What is Preemptive Priority Scheduling?**
    A1: In **Preemptive Priority Scheduling**, processes are selected based on their priority. The process with the highest priority (lowest priority number) gets executed. If a new process arrives with a higher priority than the running process, the running process is preempted.

    Q2: **How is the Finish Time calculated?**
    A2: The **Finish Time** of a process is the time when the process completes its execution. It is computed after the process finishes its remaining execution.

    Q3: **How is Turnaround Time calculated?**
    A3: **Turnaround Time** is the total time taken by a process from arrival to completion. It is calculated as:  
    \[
    \text{Turnaround Time} = \text{Finish Time} - \text{Arrival Time}
    \]

    Q4: **What is Waiting Time for each process?**
    A4: **Waiting Time** is the total time a process spends waiting in the ready queue before it starts execution. It is calculated as:  
    \[
    \text{Waiting Time} = \text{Turnaround Time} - \text{Burst Time}
    \]

    Q5: **How is starvation avoided in Priority Scheduling?**
    A5: Starvation is avoided by ensuring that processes with higher priority eventually get executed. However, without mechanisms like aging, lower priority processes can still starve if high-priority processes keep arriving.

    Q6: **What happens when two processes have the same priority?**
    A6: If two processes have the same priority, the one that arrives first will be executed first.

    Q7: **How does Preemptive Priority Scheduling work when a process arrives during execution?**
    A7: When a process arrives and has a higher priority than the currently running process, the current process is preempted, and the new process starts executing.

    Q8: **Can Preemptive Priority Scheduling lead to starvation?**
    A8: Yes, if a lower priority process is continuously preempted by higher priority processes, it can lead to starvation, which is why aging is used in some systems to prevent this.
*/


//new section //


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;                // Process ID
    int arrivalTime;       // Arrival time of the process
    int burstTime;         // Burst time of the process (time required for execution)
    int priority;          // Priority of the process (lower number means higher priority)
    int finishTime;        // Finish time
    int turnaroundTime;    // Turnaround time (Finish Time - Arrival Time)
    int waitingTime;       // Waiting time (Turnaround Time - Burst Time)
};

// Function to calculate Non-Preemptive Priority Scheduling
void calculateNonPreemptivePriorityScheduling(vector<Process>& processes) {
    int currentTime = 0;
    int completed = 0;
    int n = processes.size();

    // Sort processes by arrival time and priority
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    while (completed < n) {
        int idx = -1;
        int highestPriority = INT_MAX;

        // Find the process with the highest priority (lowest priority number) that has arrived
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrivalTime <= currentTime && processes[i].burstTime > 0) {
                if (processes[i].priority < highestPriority) {
                    highestPriority = processes[i].priority;
                    idx = i;
                }
            }
        }

        // If no process is found, move time forward
        if (idx == -1) {
            ++currentTime;
            continue;
        }

        // Process the selected process (run it to completion)
        processes[idx].finishTime = currentTime + processes[idx].burstTime;
        processes[idx].turnaroundTime = processes[idx].finishTime - processes[idx].arrivalTime;
        processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;

        // Update current time and mark the process as completed
        currentTime = processes[idx].finishTime;
        processes[idx].burstTime = 0;  // Process has finished
        completed++;
    }
}

// Function to print the results in a tabular format
void printTable(const vector<Process>& processes) {
    cout << "Process\tArrival Time\tBurst Time\tPriority\tFinish Time\tTurnaround Time\tWaiting Time\n";
    for (const auto& p : processes) {
        cout << p.id << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t" 
             << p.priority << "\t\t" << p.finishTime << "\t\t" << p.turnaroundTime << "\t\t" 
             << p.waitingTime << "\n";
    }
}

int main() {
    // Initial process data (id, arrival time, burst time, priority)
    vector<Process> processes = {
        {1, 0, 6, 2, 0, 0, 0},
        {2, 1, 8, 1, 0, 0, 0},
        {3, 2, 7, 3, 0, 0, 0},
        {4, 3, 3, 4, 0, 0, 0},
        {5, 4, 4, 2, 0, 0, 0}
    };

    // Calculate times for Non-Preemptive Priority Scheduling
    cout << "Non-Preemptive Priority Scheduling:\n";
    calculateNonPreemptivePriorityScheduling(processes);
    printTable(processes);

    return 0;  // Successful execution
}

/*
    Program Description:
    This C++ program implements the Non-Preemptive Priority Scheduling algorithm. 
    Processes are executed based on their priority. The process with the smallest priority 
    number (highest priority) is executed first. Once a process starts, it runs to completion 
    without being preempted.

    1. **Non-Preemptive Priority Scheduling**:
        - The process with the highest priority (smallest priority number) is executed first.
        - Once a process starts, it runs to completion, even if a new process with a higher priority arrives.

    FAQ Section:

    Q1: **What is Non-Preemptive Priority Scheduling?**
    A1: In **Non-Preemptive Priority Scheduling**, the process with the highest priority (lowest priority number) is selected for execution. Once a process starts executing, it runs to completion, and no other process can preempt it.

    Q2: **How is the Finish Time calculated?**
    A2: The **Finish Time** of a process is the time when the process completes its execution. In Non-Preemptive Priority Scheduling, it is calculated when the process has completed its burst time.

    Q3: **How is Turnaround Time calculated?**
    A3: **Turnaround Time** is the total time taken by a process from arrival to completion. It is calculated as:  
    \[
    \text{Turnaround Time} = \text{Finish Time} - \text{Arrival Time}
    \]

    Q4: **What is Waiting Time for each process?**
    A4: **Waiting Time** is the total time a process spends waiting in the ready queue before it starts execution. It is calculated as:  
    \[
    \text{Waiting Time} = \text{Turnaround Time} - \text{Burst Time}
    \]

    Q5: **How does this algorithm handle the case where multiple processes have the same priority?**
    A5: If two processes have the same priority, they are scheduled based on their arrival time, meaning the one that arrives first gets executed first.

    Q6: **What are the challenges of Non-Preemptive Priority Scheduling?**
    A6: One of the main challenges is **starvation**, where low-priority processes may never get executed if high-priority processes keep arriving.

    Q7: **How can we improve Non-Preemptive Priority Scheduling?**
    A7: One way to improve this scheduling algorithm is to use **aging**, which gradually increases the priority of a process that has been waiting too long in the ready queue. This helps prevent starvation.

*/

//new section//


#include <iostream>
#include <vector>
#include <algorithm>
#include<climits>
using namespace std;

struct Process {
    int id;                // Process ID
    int arrivalTime;       // Arrival time of the process
    int burstTime;         // Burst time of the process (time required for execution)
    int priority;          // Priority of the process (lower number means higher priority)
    int finishTime;        // Finish time
    int turnaroundTime;    // Turnaround time (Finish Time - Arrival Time)
    int waitingTime;       // Waiting time (Turnaround Time - Burst Time)
};

// Function to calculate Non-Preemptive Priority Scheduling
void calculateNonPreemptivePriorityScheduling(vector<Process>& processes) {
    int currentTime = 0;
    int completed = 0;
    int n = processes.size();

    // Sort processes by arrival time and priority
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    while (completed < n) {
        int idx = -1;
        int highestPriority = INT_MAX;

        // Find the process with the highest priority (lowest priority number) that has arrived
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrivalTime <= currentTime && processes[i].burstTime > 0) {
                if (processes[i].priority < highestPriority) {
                    highestPriority = processes[i].priority;
                    idx = i;
                }
            }
        }

        // If no process is found, move time forward
        if (idx == -1) {
            ++currentTime;
            continue;
        }

        // Process the selected process (run it to completion)
        processes[idx].finishTime = currentTime + processes[idx].burstTime;
        processes[idx].turnaroundTime = processes[idx].finishTime - processes[idx].arrivalTime;
        processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;

        // Update current time and mark the process as completed
        currentTime = processes[idx].finishTime;
        processes[idx].burstTime = 0;  // Process has finished
        completed++;
    }
}

// Function to print the results in a tabular format
void printTable(const vector<Process>& processes) {
    cout << "Process\tArrival Time\tBurst Time\tPriority\tFinish Time\tTurnaround Time\tWaiting Time\n";
    for (const auto& p : processes) {
        cout << p.id << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t" 
             << p.priority << "\t\t" << p.finishTime << "\t\t" << p.turnaroundTime << "\t\t" 
             << p.waitingTime << "\n";
    }
}

int main() {
    // Initial process data (id, arrival time, burst time, priority)
    vector<Process> processes = {
        {1, 0, 6, 2, 0, 0, 0},
        {2, 1, 8, 1, 0, 0, 0},
        {3, 2, 7, 3, 0, 0, 0},
        {4, 3, 3, 4, 0, 0, 0},
        {5, 4, 4, 2, 0, 0, 0}
    };

    // Calculate times for Non-Preemptive Priority Scheduling
    cout << "Non-Preemptive Priority Scheduling:\n";
    calculateNonPreemptivePriorityScheduling(processes);
    printTable(processes);

    return 0;  // Successful execution
}

/*
    Program Description:
    This C++ program implements the Non-Preemptive Priority Scheduling algorithm. 
    Processes are executed based on their priority. The process with the smallest priority 
    number (highest priority) is executed first. Once a process starts, it runs to completion 
    without being preempted.

    1. **Non-Preemptive Priority Scheduling**:
        - The process with the highest priority (smallest priority number) is executed first.
        - Once a process starts, it runs to completion, even if a new process with a higher priority arrives.

    FAQ Section:

    Q1: **What is Non-Preemptive Priority Scheduling?**
    A1: In **Non-Preemptive Priority Scheduling**, the process with the highest priority (lowest priority number) is selected for execution. Once a process starts executing, it runs to completion, and no other process can preempt it.

    Q2: **How is the Finish Time calculated?**
    A2: The **Finish Time** of a process is the time when the process completes its execution. In Non-Preemptive Priority Scheduling, it is calculated when the process has completed its burst time.

    Q3: **How is Turnaround Time calculated?**
    A3: **Turnaround Time** is the total time taken by a process from arrival to completion. It is calculated as:  
    \[
    \text{Turnaround Time} = \text{Finish Time} - \text{Arrival Time}
    \]

    Q4: **What is Waiting Time for each process?**
    A4: **Waiting Time** is the total time a process spends waiting in the ready queue before it starts execution. It is calculated as:  
    \[
    \text{Waiting Time} = \text{Turnaround Time} - \text{Burst Time}
    \]

    Q5: **How does this algorithm handle the case where multiple processes have the same priority?**
    A5: If two processes have the same priority, they are scheduled based on their arrival time, meaning the one that arrives first gets executed first.

    Q6: **What are the challenges of Non-Preemptive Priority Scheduling?**
    A6: One of the main challenges is **starvation**, where low-priority processes may never get executed if high-priority processes keep arriving.

    Q7: **How can we improve Non-Preemptive Priority Scheduling?**
    A7: One way to improve this scheduling algorithm is to use **aging**, which gradually increases the priority of a process that has been waiting too long in the ready queue. This helps prevent starvation.

*/
