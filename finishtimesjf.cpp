#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;                // Process ID
    int arrivalTime;       // Arrival time of the process
    int burstTime;         // Burst time of the process (time required for execution)
    int finishTime;        // Finish time
    int turnaroundTime;    // Turnaround time (Finish Time - Arrival Time)
    int waitingTime;       // Waiting time (Turnaround Time - Burst Time)
};

// Function for Non-Preemptive SJF
void calculateNonPreemptiveSJF(vector<Process>& processes) {
    int currentTime = 0;
    int n = processes.size();
    
    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });
    
    // Process each process one by one
    for (int i = 0; i < n; ++i) {
        // If the process arrives after the current time, jump to its arrival time
        if (processes[i].arrivalTime > currentTime) {
            currentTime = processes[i].arrivalTime;
        }

        // Set finish time for the current process
        processes[i].finishTime = currentTime + processes[i].burstTime;

        // Calculate turnaround time
        processes[i].turnaroundTime = processes[i].finishTime - processes[i].arrivalTime;

        // Calculate waiting time
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

        // Update current time for the next process
        currentTime = processes[i].finishTime;
    }
}

// Function to print the results in a tabular format
void printTable(const vector<Process>& processes) {
    cout << "Process\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n";
    for (const auto& p : processes) {
        cout << p.id << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t" 
             << p.finishTime << "\t\t" << p.turnaroundTime << "\t\t" << p.waitingTime << "\n";
    }
}

int main() {
    // Initial process data (id, arrival time, burst time)
    vector<Process> processes = {
        {1, 0, 6, 0, 0, 0},
        {2, 1, 8, 0, 0, 0},
        {3, 2, 7, 0, 0, 0},
        {4, 3, 3, 0, 0, 0},
        {5, 4, 4, 0, 0, 0}
    };

    // Calculate times for Non-Preemptive SJF
    cout << "Non-Preemptive SJF Scheduling:\n";
    calculateNonPreemptiveSJF(processes);
    printTable(processes);

    return 0;  // Successful execution
}

/*
    Program Description:
    This simplified C++ program implements the Non-Preemptive Shortest Job First (SJF) scheduling algorithm.
    It calculates and prints the **Finish Time**, **Turnaround Time**, and **Waiting Time** for each process.

    1. **Non-Preemptive SJF**:
        - Processes are executed based on their burst time. The process with the shortest burst time that is ready to execute is selected first.
        - Once a process starts execution, it runs to completion without interruption.

    FAQ Section:

    Q1: **What is the difference between Preemptive and Non-Preemptive SJF?**
    A1: In **Non-Preemptive SJF**, once a process starts, it runs to completion. In **Preemptive SJF**, the currently running process may be interrupted if a new process with a shorter remaining burst time arrives.

    Q2: **How is the Finish Time calculated?**
    A2: The Finish Time of a process is the time when the process completes its execution. In Non-Preemptive SJF, the finish time is calculated by adding the process's burst time to the current time.

    Q3: **How is Turnaround Time calculated?**
    A3: Turnaround Time is the total time taken from the arrival of a process to its completion. It is calculated as:  
    \[ \text{Turnaround Time} = \text{Finish Time} - \text{Arrival Time} \]

    Q4: **What is the Waiting Time for each process?**
    A4: Waiting Time is the time a process spends waiting in the ready queue before it starts execution. It is calculated as:  
    \[ \text{Waiting Time} = \text{Turnaround Time} - \text{Burst Time} \]

    Q5: **How can this approach be scaled for more processes?**
    A5: The approach can easily scale by adding more processes to the `processes` vector. The program will compute the finish, turnaround, and waiting times for all processes in the list.
*/


// NEW SECTION //

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;                // Process ID
    int arrivalTime;       // Arrival time of the process
    int burstTime;         // Burst time of the process (time required for execution)
    int remainingTime;     // Remaining time for preemptive SJF
    int finishTime;        // Finish time
    int turnaroundTime;    // Turnaround time (Finish Time - Arrival Time)
    int waitingTime;       // Waiting time (Turnaround Time - Burst Time)
};

// Function to calculate Preemptive SJF (Shortest Remaining Time First)
void calculatePreemptiveSJF(vector<Process>& processes) {
    int currentTime = 0;
    int completed = 0;
    int n = processes.size();
    vector<int> remainingBurstTimes(n, 0);

    // Initially, copy the burst time to remaining time
    for (int i = 0; i < n; ++i) {
        remainingBurstTimes[i] = processes[i].burstTime;
    }

    // While there are processes to complete
    while (completed < n) {
        int idx = -1;
        int shortestRemainingTime = 9999;

        // Find the process with the shortest remaining burst time that has arrived
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrivalTime <= currentTime && remainingBurstTimes[i] > 0) {
                if (remainingBurstTimes[i] < shortestRemainingTime) {
                    shortestRemainingTime = remainingBurstTimes[i];
                    idx = i;
                }
            }
        }

        // If no process is found, move time forward (idle time)
        if (idx == -1) {
            ++currentTime;
            continue;
        }

        // Process the selected process for 1 unit of time
        remainingBurstTimes[idx]--;

        // If this is the last unit of time for the process, update its finish time, turnaround time, and waiting time
        if (remainingBurstTimes[idx] == 0) {
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
    cout << "Process\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n";
    for (const auto& p : processes) {
        cout << p.id << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t" 
             << p.finishTime << "\t\t" << p.turnaroundTime << "\t\t" << p.waitingTime << "\n";
    }
}

int main() {
    // Initial process data (id, arrival time, burst time)
    vector<Process> processes = {
        {1, 0, 6, 0, 0, 0},
        {2, 1, 8, 0, 0, 0},
        {3, 2, 7, 0, 0, 0},
        {4, 3, 3, 0, 0, 0},
        {5, 4, 4, 0, 0, 0}
    };

    // Calculate times for Preemptive SJF
    cout << "Preemptive SJF Scheduling:\n";
    calculatePreemptiveSJF(processes);
    printTable(processes);

    return 0;  // Successful execution
}

/*
    Program Description:
    This C++ program implements the Preemptive Shortest Job First (SJF) scheduling algorithm, 
    also known as Shortest Remaining Time First (SRTF). The program calculates and prints 
    the **Finish Time**, **Turnaround Time**, and **Waiting Time** for each process.

    1. **Preemptive SJF (Shortest Remaining Time First)**:
        - The process with the shortest remaining burst time is executed next.
        - If a new process arrives with a shorter remaining burst time than the current running process, 
          the current process is preempted and the new process starts executing.

    FAQ Section:

    Q1: **What is the difference between Preemptive and Non-Preemptive SJF?**
    A1: In **Non-Preemptive SJF**, once a process starts executing, it cannot be preempted. The process runs to completion.  
       In **Preemptive SJF** (Shortest Remaining Time First), the running process can be preempted if a new process with a shorter burst time arrives.

    Q2: **How is the Finish Time calculated?**
    A2: The Finish Time of a process is the time when the process completes its execution. In Preemptive SJF, the process executes in multiple slices and the finish time is computed after the process completes all its execution.

    Q3: **How is Turnaround Time calculated?**
    A3: Turnaround Time is the total time taken from the arrival of a process to its completion. It is calculated as:  
    \[ \text{Turnaround Time} = \text{Finish Time} - \text{Arrival Time} \]

    Q4: **What is the Waiting Time for each process?**
    A4: Waiting Time is the time a process spends waiting in the ready queue before it starts execution. It is calculated as:  
    \[ \text{Waiting Time} = \text{Turnaround Time} - \text{Burst Time} \]

    Q5: **Can Preemptive SJF lead to starvation?**
    A5: Yes, Preemptive SJF can lead to **starvation** for long processes if shorter processes keep arriving. The shorter processes keep preempting the longer ones, potentially leading to indefinite postponement of the longer ones.

    Q6: **How does the system handle the case where multiple processes arrive at the same time?**
    A6: If multiple processes arrive at the same time, the system will select the process with the shortest burst time. If the burst times are equal, the process with the lower arrival time is chosen.

    Q7: **What are the main challenges with SJF scheduling?**
    A7: The main challenge with SJF is that it requires knowledge of the burst time of processes in advance, which is not always possible. Also, it can lead to starvation for longer processes if shorter ones keep arriving.

    Q8: **How can we improve the SJF scheduling algorithm?**
    A8: To improve SJF, we can use algorithms like **Round Robin** or introduce **priority scheduling** to ensure that long processes eventually get executed. We can also use **Estimated Burst Time** to predict the burst time of processes, rather than relying on fixed burst times.
*/
