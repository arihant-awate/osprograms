#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Structure to store the information of each process
struct Process {
    int id;                // Process ID
    int arrivalTime;       // Time at which the process arrives
    int burstTime;         // Time required by the process for execution
    int finishTime;        // Time at which the process finishes execution
    int turnaroundTime;    // Time from arrival to completion (Finish Time - Arrival Time)
    int waitingTime;       // Time spent waiting in the ready queue (Turnaround Time - Burst Time)
};

// Function to calculate the finish time, turnaround time, and waiting time for FCFS
void calculateFCFS(vector<Process>& processes) {
    int currentTime = 0;  // Variable to track the current time as processes are scheduled

    // Calculate Finish Time, Turnaround Time, and Waiting Time for each process
    for (int i = 0; i < processes.size(); i++) {
        // If the current time is less than the arrival time of the process, set current time to the arrival time
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }

        // Finish Time = current time + burst time of the process
        processes[i].finishTime = currentTime + processes[i].burstTime;

        // Turnaround Time = Finish Time - Arrival Time
        processes[i].turnaroundTime = processes[i].finishTime - processes[i].arrivalTime;

        // Waiting Time = Turnaround Time - Burst Time
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
    // Define a list of processes with id, arrival time, and burst time
    vector<Process> processes = {
        {1, 0, 4, 0, 0, 0},
        {2, 1, 3, 0, 0, 0},
        {3, 2, 1, 0, 0, 0},
        {4, 3, 2, 0, 0, 0}
    };

    // Calculate FCFS times for all processes
    calculateFCFS(processes);

    // Print the results in a table format
    printTable(processes);

    return 0; // Successful execution
}

/*
    Program Description:
    This C++ program implements the First Come First Serve (FCFS) scheduling algorithm, which is a non-preemptive scheduling algorithm. 
    The FCFS algorithm schedules processes based on their arrival time in the ready queue, meaning that the first process to arrive 
    gets executed first. The program calculates the **Finish Time**, **Turnaround Time**, and **Waiting Time** for each process 
    and displays the results in a tabular format.

    1. **Arrival Time**:
        - This is the time at which the process arrives in the ready queue.
    
    2. **Burst Time**:
        - This is the time required by the process to execute completely.
    
    3. **Finish Time**:
        - The time at which the process completes its execution.
        - It is calculated as `currentTime + burstTime` where `currentTime` is the time the process starts execution.
    
    4. **Turnaround Time**:
        - The total time taken by a process from its arrival to its completion.
        - It is calculated as `Finish Time - Arrival Time`.
    
    5. **Waiting Time**:
        - The time a process spends waiting in the ready queue before it starts execution.
        - It is calculated as `Turnaround Time - Burst Time`.

    The program handles the execution of multiple processes and prints the computed values in a table for each process, showing the important time metrics.

    FAQ Section:

    Q1: **What is the First Come First Serve (FCFS) Scheduling Algorithm?**
    A1: The First Come First Serve (FCFS) scheduling algorithm is the simplest scheduling algorithm. In this algorithm, processes are executed in the order they arrive in the ready queue. The first process to arrive is the first to be executed, and so on. It is a non-preemptive algorithm, meaning once a process starts execution, it runs to completion without interruption.

    Q2: **What is the Finish Time of a process in FCFS?**
    A2: The Finish Time of a process in FCFS is the time at which the process completes its execution. It is calculated by adding the process's burst time to the current time, which keeps track of when the process starts and finishes.

    Q3: **How is Turnaround Time calculated in FCFS?**
    A3: Turnaround Time is the total time taken by a process to complete from its arrival in the ready queue to its completion. It is calculated as:  
    \[ \text{Turnaround Time} = \text{Finish Time} - \text{Arrival Time} \]

    Q4: **What is the formula for calculating Waiting Time?**
    A4: Waiting Time is the time a process spends waiting in the ready queue before it starts execution. It is calculated as:  
    \[ \text{Waiting Time} = \text{Turnaround Time} - \text{Burst Time} \]
    It represents the time a process spends waiting for its turn to execute.

    Q5: **Why does FCFS sometimes lead to poor performance?**
    A5: The main drawback of FCFS is that it does not consider the burst times of processes. If a long process arrives before a shorter one, the shorter process will have to wait, resulting in longer turnaround and waiting times for all subsequent processes. This is known as the **convoy effect**, where short processes suffer due to long processes that arrive earlier.

    Q6: **How does FCFS differ from other scheduling algorithms like Shortest Job First (SJF)?**
    A6: In FCFS, processes are executed in the order they arrive, regardless of how long they will take to execute. In contrast, Shortest Job First (SJF) executes the process with the shortest burst time first, which minimizes average waiting time but requires knowing or estimating the burst time of each process in advance.

    Q7: **Can FCFS scheduling algorithm lead to starvation?**
    A7: No, FCFS does not lead to starvation. All processes are guaranteed to be executed in the order they arrive. However, it can result in poor turnaround and waiting times, especially if a long process arrives first.

    Q8: **How can this FCFS algorithm be improved?**
    A8: FCFS can be improved by considering the burst time of processes, such as in the **Shortest Job First (SJF)** scheduling algorithm. Another improvement could be **Preemptive Scheduling**, where processes are interrupted after a fixed time slice to allow more fairness in execution (used in Round Robin scheduling).

    Q9: **How do we handle the situation when a process arrives after another?**
    A9: In FCFS, processes are handled in the order of their arrival. When a new process arrives, it is simply placed in the queue, and when the CPU is free, the process at the front of the queue is executed first.

    Q10: **Can this approach be scaled for more processes?**
    A10: Yes, this approach can be scaled for any number of processes. The computation for each process (finish time, turnaround time, and waiting time) is done sequentially, and as long as the processes are correctly sorted based on their arrival times, the algorithm will work as expected.

    Q11: **What are the key limitations of the FCFS algorithm?**
    A11: The key limitations of FCFS are:
    - **Convoy Effect**: Shorter processes may have to wait for longer processes to finish, leading to high waiting times.
    - It can be inefficient in terms of both **waiting time** and **turnaround time**, especially for processes with a large variation in burst times.
*/
