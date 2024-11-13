#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Process {
    int id;                // Process ID
    int arrivalTime;       // Arrival time of the process
    int burstTime;         // Total burst time of the process
    int remainingTime;     // Remaining time for the process
    int finishTime;        // Finish time
    int turnaroundTime;    // Turnaround time (Finish Time - Arrival Time)
    int waitingTime;       // Waiting time (Turnaround Time - Burst Time)
};

// Function to calculate Round Robin Scheduling
void calculateRoundRobin(vector<Process>& processes, int timeQuantum) {
    int currentTime = 0;
    int n = processes.size();
    queue<int> readyQueue;
    
    // Initially, all processes are added to the ready queue
    for (int i = 0; i < n; ++i) {
        readyQueue.push(i);
        processes[i].remainingTime = processes[i].burstTime;  // Set remaining time as burst time initially
    }

    while (!readyQueue.empty()) {
        int idx = readyQueue.front();
        readyQueue.pop();

        // If the process still has remaining time
        if (processes[idx].remainingTime > 0) {
            int executionTime = min(processes[idx].remainingTime, timeQuantum);  // Execute for time quantum or remaining time
            currentTime += executionTime;  // Increment current time by execution time
            processes[idx].remainingTime -= executionTime;  // Decrease the remaining time of the process
            
            // If process is finished
            if (processes[idx].remainingTime == 0) {
                processes[idx].finishTime = currentTime;
                processes[idx].turnaroundTime = processes[idx].finishTime - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
            } else {
                // If process is not finished, put it back in the ready queue
                readyQueue.push(idx);
            }
        }
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
        {1, 0, 6, 0, 0, 0, 0},
        {2, 1, 8, 0, 0, 0, 0},
        {3, 2, 7, 0, 0, 0, 0},
        {4, 3, 3, 0, 0, 0, 0},
        {5, 4, 4, 0, 0, 0, 0}
    };

    // Time quantum for Round Robin
    int timeQuantum = 4;

    // Calculate times for Round Robin scheduling
    cout << "Round Robin Scheduling (Time Quantum = " << timeQuantum << "):\n";
    calculateRoundRobin(processes, timeQuantum);
    printTable(processes);

    return 0;  // Successful execution
}

/*
    Program Description:
    This C++ program implements the Round Robin (RR) scheduling algorithm. It calculates and prints 
    the **Finish Time**, **Turnaround Time**, and **Waiting Time** for each process.
    
    1. **Round Robin (RR)**:
        - Each process is assigned a fixed time quantum, and the CPU is allocated to each process 
          in a cyclic order. When a process's time quantum expires, it is preempted and placed at the 
          end of the ready queue. The process continues from where it was left off when it is again 
          allocated the CPU.

    FAQ Section:

    Q1: **What is Round Robin Scheduling?**
    A1: **Round Robin Scheduling** is a preemptive scheduling algorithm where each process is assigned a fixed time slice or quantum. 
       Each process is executed for a time equal to the time quantum. Once its time quantum expires, it is moved to the back of the ready queue 
       and the next process is executed. This continues cyclically.

    Q2: **How is the Finish Time calculated?**
    A2: The **Finish Time** of a process is the time when the process completes its execution. It is calculated after the process has finished 
       all its remaining burst time.

    Q3: **How is Turnaround Time calculated?**
    A3: **Turnaround Time** is the total time taken by a process from its arrival to its completion. It is calculated as:  
    \[
    \text{Turnaround Time} = \text{Finish Time} - \text{Arrival Time}
    \]

    Q4: **What is Waiting Time for each process?**
    A4: **Waiting Time** is the time a process spends waiting in the ready queue before it starts execution. It is calculated as:  
    \[
    \text{Waiting Time} = \text{Turnaround Time} - \text{Burst Time}
    \]

    Q5: **How does Round Robin Scheduling handle process preemption?**
    A5: **Round Robin Scheduling** preempts a process when its time quantum expires. The process is placed back in the ready queue and will 
       be executed again when it comes to the front of the queue. This allows for better CPU utilization and fair process allocation.

    Q6: **What is the effect of the time quantum on Round Robin scheduling?**
    A6: A smaller **time quantum** can result in higher context switching overhead, while a larger quantum may behave like **First Come, First Served (FCFS)**. The ideal time quantum is typically small enough to allow for fair CPU time but not too small to cause excessive context switches.

    Q7: **Can Round Robin Scheduling lead to starvation?**
    A7: No, **Round Robin Scheduling** does not lead to starvation since each process gets an equal opportunity to execute in a cyclic order.
*/
