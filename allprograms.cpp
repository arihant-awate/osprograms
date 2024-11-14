/* alp.cpp */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class ALPLoader {
private:
    vector<string> memory;  // Main memory represented as a vector of strings
    int memorySize;         // The size of main memory

public:
    // Constructor to initialize memory size and memory
    ALPLoader(int size) : memorySize(size) {
        memory.resize(memorySize);  // Resize the memory to fit the given size
    }

    // Function to load ALP program from the input file into main memory
    bool loadALPProgram(const string& fileName) {
        ifstream file(fileName);
        if (!file.is_open()) {
            cerr << "Error opening the file!" << endl;
            return false;
        }

        string instruction;
        int i = 0;
        
        // Load instructions from the file into the memory
        while (getline(file, instruction) && i < memorySize) {
            memory[i] = instruction;  // Store each instruction in memory
            i++;
        }

        file.close();
        return true;
    }

    // Function to print the contents of the memory
    void printMemory() {
        cout << "\nMain Memory (loaded ALP instructions):\n";
        cout << "--------------------------------------------\n";
        for (int i = 0; i < memorySize; i++) {
            if (!memory[i].empty()) {
                cout << "Memory Location " << setw(3) << i << ": " << memory[i] << endl;
            } else {
                break;  // Stop when we reach an empty memory location
            }
        }
        cout << "--------------------------------------------\n";
    }
};

int main() {
    int memorySize = 10;  // Size of the main memory (number of locations)
    string fileName = "example.txt";  // Name of the input file containing the ALP program

    ALPLoader loader(memorySize);

    // Load the ALP program from the file into main memory
    if (loader.loadALPProgram(fileName)) {
        // Print the loaded memory
        loader.printMemory();
    } else {
        cerr << "Failed to load ALP program!" << endl;
    }

    return 0;
}

/*
    Program Description:
    This C++ program simulates the loading of an Assembly Language Program (ALP) from an input file into the main memory. 
    The ALP program is represented as a text file where each instruction is placed on a separate line. 
    The program loads each instruction from the file into an array (simulating memory) and prints the memory content.

    FAQ Section:

    Q1: **What is an ALP program in this context?**
    A1: An **ALP program** is a sequence of assembly language instructions that are read from an input file and stored in memory. Each line in the file represents a single instruction.

    Q2: **How does the program load the ALP into memory?**
    A2: The program reads each instruction from the file line by line and stores it in the corresponding memory location in the memory array (simulated as a vector in this case).

    Q3: **What happens if the input file is too large for memory?**
    A3: If the input file contains more instructions than the available memory, only the first `memorySize` instructions are loaded. Any extra instructions are ignored.

    Q4: **Can the program handle any ALP format?**
    A4: Yes, as long as the ALP format is simple (one instruction per line), the program can handle it. The instructions are stored as strings.

    Q5: **How does the program display the memory?**
    A5: After loading the ALP program into memory, the program prints the contents of the memory locations, showing each instruction stored in memory.
*/


// new section //
/*MOV A, 1
ADD B, A
SUB C, B
JMP 100 */



/* bankers.cpp */

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



/* cscandisk.cpp */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

class CSKAN {
private:
    vector<int> requests;  // Vector to store the disk requests
    int initialPosition;   // Initial position of the disk arm
    int diskSize;          // Total size of the disk (maximum possible track number)

public:
    // Constructor to initialize requests, initial position, and disk size
    CSKAN(vector<int>& reqs, int initialPos, int size) : requests(reqs), initialPosition(initialPos), diskSize(size) {}

    // Function to simulate C-SCAN disk scheduling and calculate total seek time
    int calculateSeekTime(bool direction) {
        int totalSeekTime = 0;
        int currentPosition = initialPosition;  // Set initial position to current position

        vector<int> left, right;

        // Divide requests into left and right of the initial position
        for (int request : requests) {
            if (request < currentPosition) {
                left.push_back(request);
            } else {
                right.push_back(request);
            }
        }

        // Sort the requests in ascending order
        sort(left.begin(), left.end());
        sort(right.begin(), right.end());

        // If the direction is true, go towards the right, else go towards the left
        if (direction) {
            // Process the right side first
            totalSeekTime += abs(currentPosition - right.back());  // Move to the rightmost request
            currentPosition = right.back();

            // Serve requests on the right side
            for (int req : right) {
                totalSeekTime += abs(currentPosition - req);
                currentPosition = req;
            }

            // Jump to the lowest position in the disk
            totalSeekTime += abs(currentPosition - 0);  // Jump back to position 0
            currentPosition = 0;

            // Serve requests on the left side
            for (int req : left) {
                totalSeekTime += abs(currentPosition - req);
                currentPosition = req;
            }
        } else {
            // Process the left side first
            totalSeekTime += abs(currentPosition - left.front());  // Move to the leftmost request
            currentPosition = left.front();

            // Serve requests on the left side
            for (int req : left) {
                totalSeekTime += abs(currentPosition - req);
                currentPosition = req;
            }

            // Jump to the highest position in the disk
            totalSeekTime += abs(currentPosition - diskSize);  // Jump back to the highest position
            currentPosition = diskSize;

            // Serve requests on the right side
            for (int req : right) {
                totalSeekTime += abs(currentPosition - req);
                currentPosition = req;
            }
        }

        return totalSeekTime;
    }

    // Function to print the results in tabular format
    void printResults(bool direction) {
        cout << "\nC-SCAN Disk Scheduling Algorithm\n";
        cout << "---------------------------------\n";
        cout << "Initial Position of the Disk Arm: " << initialPosition << endl;
        cout << "Disk Size: " << diskSize << endl;
        cout << "Disk Requests: ";

        // Print the request sequence
        for (int i = 0; i < requests.size(); i++) {
            cout << requests[i] << " ";
        }
        cout << endl;

        // Calculate and print the total seek time
        int totalSeekTime = calculateSeekTime(direction);
        cout << "Total Seek Time: " << totalSeekTime << endl;

        // Print the table of movement
        cout << "\nDisk Scheduling (C-SCAN):\n";
        cout << "Current Position -> Request -> Seek Time\n";
        int currentPosition = initialPosition;
        int seekTime = 0;

        vector<int> left, right;

        // Divide requests into left and right of the initial position
        for (int request : requests) {
            if (request < currentPosition) {
                left.push_back(request);
            } else {
                right.push_back(request);
            }
        }

        // Sort the requests in ascending order
        sort(left.begin(), left.end());
        sort(right.begin(), right.end());

        if (direction) {
            // Process the right side first
            seekTime = abs(currentPosition - right.back());
            cout << setw(14) << currentPosition << setw(12) << right.back() << setw(14) << seekTime << endl;
            currentPosition = right.back();

            // Serve requests on the right side
            for (int req : right) {
                seekTime = abs(currentPosition - req);
                cout << setw(14) << currentPosition << setw(12) << req << setw(14) << seekTime << endl;
                currentPosition = req;
            }

            // Jump to the lowest position in the disk
            seekTime = abs(currentPosition - 0);
            cout << setw(14) << currentPosition << setw(12) << 0 << setw(14) << seekTime << endl;
            currentPosition = 0;

            // Serve requests on the left side
            for (int req : left) {
                seekTime = abs(currentPosition - req);
                cout << setw(14) << currentPosition << setw(12) << req << setw(14) << seekTime << endl;
                currentPosition = req;
            }
        } else {
            // Process the left side first
            seekTime = abs(currentPosition - left.front());
            cout << setw(14) << currentPosition << setw(12) << left.front() << setw(14) << seekTime << endl;
            currentPosition = left.front();

            // Serve requests on the left side
            for (int req : left) {
                seekTime = abs(currentPosition - req);
                cout << setw(14) << currentPosition << setw(12) << req << setw(14) << seekTime << endl;
                currentPosition = req;
            }

            // Jump to the highest position in the disk
            seekTime = abs(currentPosition - diskSize);
            cout << setw(14) << currentPosition << setw(12) << diskSize << setw(14) << seekTime << endl;
            currentPosition = diskSize;

            // Serve requests on the right side
            for (int req : right) {
                seekTime = abs(currentPosition - req);
                cout << setw(14) << currentPosition << setw(12) << req << setw(14) << seekTime << endl;
                currentPosition = req;
            }
        }

        cout << "\nTotal Seek Time: " << totalSeekTime << endl;
    }
};

int main() {
    // Hardcoded disk requests, initial position of the disk arm, and disk size
    vector<int> requests = {98, 183, 37, 122, 14, 124, 65, 67};
    int initialPosition = 53;
    int diskSize = 200;  // Total size of the disk (maximum possible track number)

    // Create C-SCAN object
    CSKAN cscan(requests, initialPosition, diskSize);

    // Print results and seek time (direction true = right, false = left)
    cscan.printResults(true);  // Try with direction as 'true' (right)

    return 0;
}

/*
    Program Description:
    This C++ program simulates the **C-SCAN (Circular SCAN)** disk scheduling algorithm. The program calculates 
    the total seek time and prints the input requests and corresponding output in a tabular format.

    The program calculates the page faults for a given reference string and outputs the number of page faults.

    FAQ Section:

    Q1: **What is C-SCAN disk scheduling?**
    A1: **C-SCAN (Circular SCAN)** disk scheduling algorithm moves the disk arm towards one end of the disk, services 
       requests along the way, and then jumps back to the other end without servicing any requests in between. It continues 
       in the same direction after the jump.

    Q2: **How is the seek time calculated?**
    A2: **Seek Time** is the absolute difference between the current position of the disk arm and the requested position. 
       The total seek time is the sum of the seek times for each request.

    Q3: **What happens when the disk arm reaches the end?**
    A3: When the disk arm reaches the end, it jumps back to the opposite end of the disk and continues servicing requests 
       in the same direction.

    Q4: **Is C-SCAN optimal?**
    A4: **C-SCAN** is more efficient than **FCFS** and **SCAN** as it minimizes the travel distance by always servicing 
       requests in one direction, but it may still cause waiting for requests at the farthest ends.
*/



/* deadlockdetection.cpp */

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



/* diningsemaphore.cpp */

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>  // For sleep()

using namespace std;

// Define the number of philosophers
#define NUM_PHILOSOPHERS 5

// Semaphores for each fork
sem_t forks[NUM_PHILOSOPHERS];

// Mutex for synchronizing philosophers' thinking and eating behavior
sem_t mutex;

// Philosopher thread function
void* philosopher(void* arg) {
    int id = *(int*)arg;  // Philosopher ID

    while (true) {
        // Thinking
        cout << "Philosopher " << id << " is thinking." << endl;
        sleep(2);  // Simulate thinking time

        // Trying to pick up both forks (left and right)
        sem_wait(&forks[id]);    // Pick up left fork
        sem_wait(&forks[(id + 1) % NUM_PHILOSOPHERS]);  // Pick up right fork

        // Eating
        cout << "Philosopher " << id << " is eating." << endl;
        sleep(1);  // Simulate eating time

        // Put down both forks
        sem_post(&forks[id]);    // Put down left fork
        sem_post(&forks[(id + 1) % NUM_PHILOSOPHERS]);  // Put down right fork
    }

    return nullptr;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    // Initialize semaphores for forks
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        sem_init(&forks[i], 0, 1);  // Each fork starts as available (1)
    }

    // Initialize mutex for philosopher behavior synchronization
    sem_init(&mutex, 0, 1);  // Mutex to prevent simultaneous access to shared behavior

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        ids[i] = i;
        pthread_create(&philosophers[i], nullptr, philosopher, &ids[i]);
    }

    // Join all threads
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_join(philosophers[i], nullptr);
    }

    // Clean up semaphores (not reached in this code as philosophers run infinitely)
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        sem_destroy(&forks[i]);
    }
    sem_destroy(&mutex);

    return 0;
}

/*
    Program Description:
    This C++ program implements the Dining Philosophers problem using threads and semaphores. The philosophers alternate between thinking and eating. 
    The problem ensures that no two philosophers are allowed to eat at the same time, preventing deadlock and starvation.

    1. **Forks**:
        - The forks are represented by semaphores, where each fork is initially available (set to 1). Philosophers need to acquire both the left and right forks before eating.

    2. **Philosopher Threads**:
        - Each philosopher alternates between thinking and eating. 
        - To eat, they pick up the left and right forks using the corresponding semaphores. Once they are done eating, they put down the forks.

    3. **Synchronization**:
        - The semaphores for the forks ensure that no two philosophers can eat at the same time by preventing simultaneous access to shared resources (the forks).
        - Each philosopher uses two semaphores: one for the left fork and one for the right fork. They also use a mutex to manage their thinking and eating states.

    4. **Thread Creation and Joining**:
        - The program creates multiple philosopher threads using `pthread_create()` and waits for all threads to complete using `pthread_join()`.

    FAQ Section:

    Q1: **What is the purpose of using semaphores in the Dining Philosophers problem?**  
    A1: Semaphores are used to control access to the shared resources (the forks) in the Dining Philosophers problem. Each fork is represented by a semaphore, which ensures that only one philosopher can use a fork at a time. This prevents deadlock and ensures that philosophers do not block each other unnecessarily.

    Q2: **Why do philosophers need both forks to eat?**  
    A2: Philosophers need both forks (one on the left and one on the right) to eat. This simulates the need for two resources to perform a task (eating in this case), which mirrors the real-world requirement for resources that must be shared.

    Q3: **What happens if a philosopher cannot pick up both forks?**  
    A3: If a philosopher cannot pick up both forks (because the forks are being used by others), the philosopher will wait (i.e., block) until both forks are available. This prevents simultaneous access to the forks by two philosophers.

    Q4: **Why do philosophers alternate between thinking and eating?**  
    A4: Philosophers alternate between thinking and eating to simulate real-life behavior where individuals perform tasks (thinking) and take breaks to refresh (eating). This alternation also helps prevent deadlock by allowing other philosophers to access the forks when one philosopher is thinking.

    Q5: **What prevents deadlock in this solution?**  
    A5: Deadlock is prevented because each philosopher picks up the left fork first and then the right fork. This order ensures that no philosopher can pick up both forks at the same time, and no philosopher can block others from accessing forks. Philosophers do not wait indefinitely if they cannot acquire both forks.

    Q6: **How does a philosopher know when to stop thinking and start eating?**  
    A6: Philosophers are programmed to repeatedly think and eat in a loop. They will pick up both forks only when they are ready to eat. The semaphores ensure that a philosopher can only eat when both forks are available.

    Q7: **What happens when a philosopher finishes eating?**  
    A7: Once a philosopher finishes eating, they put down both forks (release the corresponding semaphores) and resume thinking. The semaphores allow other philosophers to access the forks if they are available.

    Q8: **How does this implementation prevent starvation?**  
    A8: This solution avoids starvation because philosophers are not blocked indefinitely. Even though each philosopher may wait for the forks, no philosopher is stuck in a perpetual state of waiting, and each philosopher will eventually eat because they will be able to pick up both forks at some point.

    Q9: **What happens if all philosophers try to pick up the left fork at the same time?**  
    A9: If all philosophers try to pick up the left fork at the same time, they will each be blocked on the semaphore for the left fork. Once one philosopher is able to pick up the left fork and subsequently the right fork, they can eat and release the forks. This blocking mechanism ensures that no two philosophers can access the same fork at the same time.

    Q10: **Can we scale this solution for more philosophers?**  
    A10: Yes, this solution can be scaled for more philosophers by adjusting the number of philosopher threads and the number of semaphores representing forks. The logic remains the same, but as more philosophers are added, it becomes increasingly important to ensure proper synchronization to avoid deadlock.

    Q11: **Why do we need a mutex here?**  
    A11: The mutex is used to ensure that philosopher actions (thinking and eating) are synchronized. Without the mutex, philosophers could try to think and eat at the same time, leading to potential race conditions or inconsistency in output.

    Q12: **What are the limitations of this approach?**  
    A12: While this approach works well for a small number of philosophers, it may lead to inefficiencies or deadlock in larger systems with many philosophers. Improvements such as introducing a timeout for waiting philosophers or changing the order in which forks are picked up can help address such issues in more complex systems.
*/



/* fcfsdisk.cpp */

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

class FCFS {
private:
    vector<int> requests;  // Vector to store the disk requests
    int initialPosition;   // Initial position of the disk arm

public:
    // Constructor to initialize requests and initial position
    FCFS(vector<int>& reqs, int initialPos) : requests(reqs), initialPosition(initialPos) {}

    // Function to simulate FCFS disk scheduling and calculate total seek time
    int calculateSeekTime() {
        int totalSeekTime = 0;
        int currentPosition = initialPosition;  // Set initial position to current position

        // Iterate through all the requests
        for (int i = 0; i < requests.size(); i++) {
            // Calculate seek time for each request (absolute difference)
            totalSeekTime += abs(currentPosition - requests[i]);
            // Move disk arm to the requested position
            currentPosition = requests[i];
        }

        return totalSeekTime;
    }

    // Function to print the results in tabular format
    void printResults() {
        cout << "\nFCFS Disk Scheduling Algorithm\n";
        cout << "---------------------------------\n";
        cout << "Initial Position of the Disk Arm: " << initialPosition << endl;
        cout << "Disk Requests: ";

        // Print the request sequence
        for (int i = 0; i < requests.size(); i++) {
            cout << requests[i] << " ";
        }
        cout << endl;

        // Calculate and print the total seek time
        int totalSeekTime = calculateSeekTime();
        cout << "Total Seek Time: " << totalSeekTime << endl;

        // Print the table of movement
        cout << "\nDisk Scheduling (FCFS):\n";
        cout << "Current Position -> Request -> Seek Time\n";
        int currentPosition = initialPosition;
        int seekTime = 0;

        for (int i = 0; i < requests.size(); i++) {
            seekTime = abs(currentPosition - requests[i]);
            cout << setw(14) << currentPosition << setw(12) << requests[i] << setw(14) << seekTime << endl;
            currentPosition = requests[i];
        }

        cout << "\nTotal Seek Time: " << totalSeekTime << endl;
    }
};

int main() {
    // Hardcoded disk requests and initial position of the disk arm
    vector<int> requests = {98, 183, 37, 122, 14, 124, 65, 67};
    int initialPosition = 53;

    // Create FCFS object
    FCFS fcfs(requests, initialPosition);

    // Print results and seek time
    fcfs.printResults();

    return 0;
}

/*
    Program Description:
    This C++ program simulates the **FCFS (First-Come, First-Served)** disk scheduling algorithm. The program calculates 
    the total seek time and prints the input requests and corresponding output in a tabular format.

    FAQ Section:

    Q1: **What is FCFS disk scheduling?**
    A1: **FCFS (First-Come, First-Served)** disk scheduling algorithm handles disk requests in the order they arrive. The disk arm moves to each requested track in the given order.

    Q2: **How is the seek time calculated?**
    A2: **Seek Time** is the absolute difference between the current position of the disk arm and the requested position. The total seek time is the sum of the seek times for each request.

    Q3: **What happens when a disk request is served?**
    A3: Once a request is served, the disk arm moves to the requested track, and the next request is processed in the order it appears.

    Q4: **Is FCFS optimal?**
    A4: No, FCFS is not optimal. It does not minimize the total seek time as compared to other algorithms like **SSTF** (Shortest Seek Time First) or **SCAN**.

    Q5: **What is the main limitation of FCFS?**
    A5: The main limitation of **FCFS** is that it may lead to a high total seek time, especially if requests are scattered across the disk. It does not consider the proximity of requests to minimize arm movement.
*/



/* finishtimefcfs.cpp */

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



/* finishtimepriority.cpp */

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



/* finishtimeroundrobin.cpp */

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



/* finishtimesjf.cpp */

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



/* matrixoperations.cpp */

#include <iostream>
#include <pthread.h>    // For pthread functionality
#include <vector>       // For dynamic arrays (vectors)
#include <cstring>      // For strerror() and error handling
#include <errno.h>      // For error number definitions

using namespace std;

// Matrix dimensions (for simplicity, we assume square matrices)
#define N 4  // Size of the matrix (N x N)

// Matrix data
int matrix1[N][N] = {{1, 2, 3, 4},
                     {5, 6, 7, 8},
                     {9, 10, 11, 12},
                     {13, 14, 15, 16}};

int matrix2[N][N] = {{16, 15, 14, 13},
                     {12, 11, 10, 9},
                     {8, 7, 6, 5},
                     {4, 3, 2, 1}};

int result[N][N];  // Result matrix to store the multiplication result

// Structure to pass data to the threads
struct ThreadData {
    int row;  // Row number to process
};

// Function to multiply a row by the second matrix
void* multiplyRow(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    int row = data->row;

    for (int col = 0; col < N; col++) {
        result[row][col] = 0;
        for (int k = 0; k < N; k++) {
            result[row][col] += matrix1[row][k] * matrix2[k][col];
        }
    }
    
    pthread_exit(0); // Exit the thread after completing its task
}

int main() {
    pthread_t threads[N];  // Array of threads
    ThreadData data[N];    // Array of data for each thread

    // Create threads to perform matrix multiplication
    for (int i = 0; i < N; i++) {
        data[i].row = i;  // Assign each thread a row to compute
        if (pthread_create(&threads[i], NULL, multiplyRow, (void*)&data[i]) != 0) {
            cerr << "Failed to create thread: " << strerror(errno) << endl;
            return 1; // Exit with error if thread creation fails
        }
    }

    // Wait for all threads to complete their execution
    for (int i = 0; i < N; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            cerr << "Failed to join thread: " << strerror(errno) << endl;
            return 1; // Exit with error if thread join fails
        }
    }

    // Display the result matrix
    cout << "Resultant Matrix: " << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    return 0; // Successful execution
}

/*
    Program Description:
    This C++ program demonstrates the use of multithreading for matrix multiplication using Pthreads.
    The program multiplies two N x N matrices using N threads. Each thread is responsible for calculating 
    one row of the resultant matrix. It uses the Pthreads library to create and manage threads.

    1. **Matrix Initialization**: 
        - Two matrices, `matrix1` and `matrix2`, are initialized with predefined values.
        - A result matrix, `result`, is created to store the multiplication output.

    2. **Thread Creation**:
        - The program creates `N` threads, where each thread computes one row of the resulting matrix.
        - The `multiplyRow` function computes one row of the matrix by multiplying corresponding rows of `matrix1` and `matrix2`.

    3. **Thread Synchronization**:
        - The `pthread_join()` function is used to ensure that the main program waits for all threads to finish their execution before proceeding.

    4. **Output**:
        - Once all threads finish their task, the result matrix is displayed.

    FAQ Section:

    Q1: What is the purpose of using Pthreads in this program?
    A1: Pthreads are used to perform matrix multiplication in parallel by dividing the task of calculating the result matrix into multiple threads, each handling a different row of the result matrix. This improves performance, especially for large matrices.

    Q2: How does the `pthread_create()` function work?
    A2: The `pthread_create()` function is used to create a new thread. It takes the thread identifier, attributes (NULL for default), the function to execute, and the argument to pass to the function. In this case, the function `multiplyRow` is executed by each thread.

    Q3: What does the `pthread_join()` function do?
    A3: `pthread_join()` is used to wait for a thread to terminate. It ensures that the main thread (main program) will not proceed until all the worker threads have finished their execution.

    Q4: Why are we passing a struct to each thread?
    A4: The struct `ThreadData` is used to pass data to the threads. Each thread requires the row number to compute, so we pass a struct containing this data to the thread function.

    Q5: What happens if the `pthread_create()` or `pthread_join()` call fails?
    A5: If `pthread_create()` or `pthread_join()` fails, an error message is displayed using `strerror()` and `errno`, and the program exits with an error code.

    Q6: How does matrix multiplication work in this program?
    A6: Matrix multiplication involves multiplying the rows of the first matrix by the columns of the second matrix and summing the products. Each thread in this program computes one row of the result matrix by performing this operation.

    Q7: How can this approach be extended to larger matrices?
    A7: This approach can be scaled to larger matrices by adjusting the matrix size (N) and creating additional threads accordingly. The parallelism improves as more threads are used for larger matrices.

*/



/* opcoreerror.cpp */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class JobProcessor {
private:
    vector<string> validOpcodes = {"MOV", "ADD", "SUB", "JMP", "NOP"}; // List of valid opcodes

public:
    // Function to check for invalid opcodes and simulate raising an interrupt
    void checkForOpcodeError(const vector<string>& job) {
        for (const string& instruction : job) {
            // Get the opcode (the first word in the instruction)
            stringstream ss(instruction);
            string opcode;
            ss >> opcode;

            // Check if the opcode is valid
            if (find(validOpcodes.begin(), validOpcodes.end(), opcode) == validOpcodes.end()) {
                // If the opcode is invalid, raise an interrupt (handle error)
                raiseInterrupt(opcode);
                return; // Exit after raising the interrupt
            }
        }

        cout << "All instructions are valid. No errors detected." << endl;
    }

    // Function to simulate raising an interrupt when an invalid opcode is found
    void raiseInterrupt(const string& invalidOpcode) {
        cout << "ERROR: Invalid opcode encountered: " << invalidOpcode << endl;
        cout << "Raising interrupt to handle the error." << endl;
        // Simulating interrupt handling (could be a termination or logging)
        exit(1);  // Simulate terminating the program with an error
    }
};

int main() {
    // Example job with opcodes
    vector<string> job = {
        "MOV A, 5",
        "ADD A, B",
        "INVALID_OP X, Y",  // This is an invalid opcode for simulation
        "JMP 100"
    };

    JobProcessor processor;

    // Check the job for opcode errors
    processor.checkForOpcodeError(job);

    return 0;
}

/*
    Program Description:
    This C++ program simulates the detection of an **Opcode Error** in a given job. The program checks each instruction 
    to ensure it contains a valid opcode. If an invalid opcode is found, it raises an interrupt (simulated by printing 
    an error message and terminating the program).

    FAQ Section:

    Q1: **What is an Opcode Error?**
    A1: An **Opcode Error** occurs when the processor encounters an invalid or unrecognized instruction (opcode) during 
       the execution of a job.

    Q2: **How does the program check for opcode errors?**
    A2: The program reads each instruction in the job, extracts the opcode, and checks if it belongs to a predefined list 
       of valid opcodes. If the opcode is not valid, an interrupt is raised.

    Q3: **What happens when an invalid opcode is detected?**
    A3: If an invalid opcode is encountered, the program raises an interrupt, prints an error message, and terminates the program.

    Q4: **What are the valid opcodes in this program?**
    A4: The valid opcodes in this program are: `MOV`, `ADD`, `SUB`, `JMP`, and `NOP`. Any other opcode is considered invalid.

    Q5: **How does the interrupt mechanism work in the simulation?**
    A5: The interrupt mechanism is simulated by printing an error message and terminating the program using the `exit(1)` function.
*/



/* opranderror.cpp */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm> // Include algorithm for find()

using namespace std;

class JobProcessor {
private:
    vector<string> validRegisters = {"A", "B", "C", "D"}; // List of valid registers

public:
    // Function to check for operand errors and simulate raising an interrupt
    void checkForOperandError(const vector<string>& job) {
        for (const string& instruction : job) {
            // Parse the instruction to get the operand(s)
            stringstream ss(instruction);
            string opcode, operand1, operand2;
            ss >> opcode >> operand1;

            // Check if the instruction has two operands (for instructions like ADD, MOV, etc.)
            if (ss >> operand2) {
                if (!isValidOperand(operand1) || !isValidOperand(operand2)) {
                    // If any operand is invalid, raise an interrupt
                    raiseInterrupt(instruction);
                    return; // Exit after raising the interrupt
                }
            } else {
                if (!isValidOperand(operand1)) {
                    // If the single operand is invalid, raise an interrupt
                    raiseInterrupt(instruction);
                    return; // Exit after raising the interrupt
                }
            }
        }

        cout << "All instructions are valid. No operand errors detected." << endl;
    }

    // Function to check if an operand is valid (either a register or a number)
    bool isValidOperand(const string& operand) {
        // Check if the operand is a valid register
        if (find(validRegisters.begin(), validRegisters.end(), operand) != validRegisters.end()) {
            return true;
        }

        // Check if the operand is a valid number (could be negative, integer)
        for (char c : operand) {
            if (!isdigit(c) && c != '-') {
                return false;
            }
        }

        return true;
    }

    // Function to simulate raising an interrupt when an invalid operand is found
    void raiseInterrupt(const string& invalidInstruction) {
        cout << "ERROR: Invalid operand in instruction: " << invalidInstruction << endl;
        cout << "Raising interrupt to handle the error." << endl;
        // Simulating interrupt handling (could be a termination or logging)
        exit(1);  // Simulate terminating the program with an error
    }
};

int main() {
    // Example job with opcodes and operands
    vector<string> job = {
        "MOV A, 5",        // Valid instruction
        "ADD A, B",        // Valid instruction
        "MOV X, 10",       // Invalid operand (X is not a valid register)
        "SUB A, -3",       // Valid instruction with negative number operand
        "JMP 100"          // Invalid instruction without operand
    };

    JobProcessor processor;

    // Check the job for operand errors
    processor.checkForOperandError(job);

    return 0;
}

/*
    Program Description:
    This C++ program simulates the detection of an **Operand Error** in a given job. The program checks each instruction 
    to ensure it contains valid operands. If an invalid operand is found (either an invalid register or an invalid number), 
    it raises an interrupt (simulated by printing an error message and terminating the program).

    FAQ Section:

    Q1: **What is an Operand Error?**
    A1: An **Operand Error** occurs when the operand used in an instruction is invalid. The operand could be an invalid register 
       or an invalid number that the processor cannot recognize.

    Q2: **How does the program check for operand errors?**
    A2: The program checks each instruction for valid operands by validating whether the operand is a recognized register or a 
       valid number.

    Q3: **What happens when an invalid operand is detected?**
    A3: If an invalid operand is encountered, the program raises an interrupt by printing an error message and terminating the program.

    Q4: **How does the program validate operands?**
    A4: The program checks if the operand is either a valid register (e.g., `A`, `B`, `C`, `D`) or a valid number (including 
       negative numbers). If the operand does not meet these conditions, it is considered invalid.

    Q5: **How does the interrupt mechanism work in the simulation?**
    A5: The interrupt mechanism is simulated by printing an error message and terminating the program using the `exit(1)` function.
*/



/* pagefaultlru.cpp */

#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>

using namespace std;

class LRUPageReplacement {
private:
    int capacity;  // Maximum number of pages that can be in memory
    list<int> cache;  // List to store the pages in memory, with the most recently used at the front
    unordered_map<int, list<int>::iterator> pageMap;  // Map to store the page and its corresponding iterator in the list

public:
    LRUPageReplacement(int cap) : capacity(cap) {}

    // Function to simulate the LRU page replacement
    int calculatePageFaults(const vector<int>& referenceString) {
        int pageFaults = 0;

        for (int page : referenceString) {
            // If the page is already in memory (cache hit), move it to the front (most recently used)
            if (pageMap.find(page) != pageMap.end()) {
                cache.erase(pageMap[page]);
                cache.push_front(page);
                pageMap[page] = cache.begin();
            } else {
                // If the page is not in memory (page fault)
                pageFaults++;

                // If memory is full, remove the least recently used page
                if (cache.size() == capacity) {
                    int lruPage = cache.back();
                    cache.pop_back();
                    pageMap.erase(lruPage);
                }

                // Add the new page to the front of the cache
                cache.push_front(page);
                pageMap[page] = cache.begin();
            }
        }

        return pageFaults;
    }
};

int main() {
    // Hardcoded reference string and cache size (number of frames)
    vector<int> referenceString = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3};
    int numFrames = 3;  // Number of page frames in memory

    // Create an LRUPageReplacement object with the given number of frames
    LRUPageReplacement lru(numFrames);

    // Calculate the number of page faults
    int pageFaults = lru.calculatePageFaults(referenceString);

    // Output the result
    cout << "Number of page faults: " << pageFaults << endl;

    return 0;
}

/*
    Program Description:
    This C++ program simulates the **LRU (Least Recently Used)** page replacement algorithm to calculate 
    the number of page faults. The program uses a **list** to store the pages in memory and an **unordered_map** 
    to quickly check if a page is in memory.

    The program calculates the page faults for a given reference string and outputs the number of page faults.

    FAQ Section:

    Q1: **What is a page fault?**
    A1: A **page fault** occurs when a process tries to access a page that is not currently in memory. The operating 
       system must load the page into memory, which is typically done from disk storage.

    Q2: **How does the LRU page replacement algorithm work?**
    A2: The **LRU** algorithm replaces the page that has not been used for the longest time. It keeps track of the order 
       in which pages were accessed and replaces the least recently used page when a new page is required but memory is full.

    Q3: **How are page faults counted in this program?**
    A3: A page fault occurs whenever a process attempts to access a page that is not currently in memory. The program 
       counts how many such page accesses occur while processing the reference string.

    Q4: **What happens when the memory (cache) is full?**
    A4: When the memory is full, the **LRU** algorithm removes the least recently used page and replaces it with the 
       new page that caused the page fault.

    Q5: **What data structures are used in this program?**
    A5: The program uses a **list** to store the pages in memory, with the most recently used page at the front. 
       An **unordered_map** is used to map pages to their respective positions in the list for fast access.

    Q6: **Can this approach be extended for larger memory sizes?**
    A6: Yes, the program can be easily extended to handle larger memory sizes by adjusting the `numFrames` variable 
       to represent the desired memory capacity.
*/



/* pagefaultsfifo.cpp */

#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

int fifoPageFaults(vector<int>& referenceString, int numFrames) {
    unordered_set<int> pagesInMemory;  // To keep track of pages in memory
    queue<int> pageQueue;  // Queue to implement FIFO
    int pageFaults = 0;

    // Traverse through the reference string
    for (int page : referenceString) {
        // If page is not in memory, we have a page fault
        if (pagesInMemory.find(page) == pagesInMemory.end()) {
            // If memory is not full, just add the page
            if (pagesInMemory.size() < numFrames) {
                pagesInMemory.insert(page);
                pageQueue.push(page);
            } else {
                // If memory is full, remove the oldest page (FIFO) and add the new page
                int oldestPage = pageQueue.front();
                pageQueue.pop();
                pagesInMemory.erase(oldestPage); // Remove the oldest page
                pagesInMemory.insert(page);  // Add the new page
                pageQueue.push(page);  // Add the new page to the queue
            }
            pageFaults++;  // Increase page fault count
        }
    }
    
    return pageFaults;  // Return the number of page faults
}

int main() {
    // Example: Reference string and number of frames
    vector<int> referenceString = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3};
    int numFrames = 3;  // Number of page frames in memory

    int pageFaults = fifoPageFaults(referenceString, numFrames);

    cout << "Number of page faults: " << pageFaults << endl;

    return 0;
}

/*
    Program Description:
    This C++ program calculates the number of page faults for a given reference string using the **FIFO (First In First Out)** 
    page replacement algorithm. The program simulates a memory with a fixed number of frames and calculates how many times 
    a page fault occurs when accessing pages in the reference string.

    FAQ Section:

    Q1: **What is a page fault?**
    A1: A **page fault** occurs when a process tries to access a page that is not currently in memory. The system must load 
    the page from disk into memory, which can be slow.

    Q2: **What is FIFO in page replacement?**
    A2: **FIFO (First In First Out)** is a page replacement algorithm where the oldest page in memory (the page that arrived 
    first) is replaced when a new page needs to be loaded, and there is no free space left.

    Q3: **How does the FIFO algorithm work?**
    A3: The FIFO algorithm maintains a queue of pages in memory. When a new page needs to be loaded, if memory is full, 
    the page at the front of the queue (the oldest page) is removed and replaced by the new page.

    Q4: **How are page faults counted in this program?**
    A4: The program counts how many times a page is not in memory when accessed. If the page is not in memory, it's a page fault. 

    Q5: **How does the program handle memory frames?**
    A5: The program keeps track of the pages in memory using a **queue** and a **set** to ensure that each page is loaded 
    only once until it is replaced by a newer one.
*/



/* pagefaultsoptimal.cpp */

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

class OptimalPageReplacement {
private:
    int capacity;  // Number of frames in memory

public:
    OptimalPageReplacement(int cap) : capacity(cap) {}

    // Function to simulate the Optimal page replacement algorithm
    int calculatePageFaults(const vector<int>& referenceString) {
        int pageFaults = 0;
        unordered_set<int> pagesInMemory;  // To keep track of pages in memory

        for (int i = 0; i < referenceString.size(); i++) {
            int page = referenceString[i];

            // If page is already in memory, no page fault
            if (pagesInMemory.find(page) != pagesInMemory.end()) {
                continue;
            }

            // If memory is not full, add the page
            if (pagesInMemory.size() < capacity) {
                pagesInMemory.insert(page);
                pageFaults++;
            } else {
                // If memory is full, replace the page using the Optimal strategy
                int farthest = -1;
                int pageToReplace = -1;

                // Find the page that will not be used for the longest time in the future
                for (int p : pagesInMemory) {
                    int j;
                    for (j = i + 1; j < referenceString.size(); j++) {
                        if (referenceString[j] == p) {
                            break;
                        }
                    }

                    // If page is not found in future, it's the optimal candidate for replacement
                    if (j == referenceString.size()) {
                        pageToReplace = p;
                        break;
                    }

                    // Find the page that is used farthest in the future
                    if (j > farthest) {
                        farthest = j;
                        pageToReplace = p;
                    }
                }

                // Replace the pageToReplace with the new page
                pagesInMemory.erase(pageToReplace);
                pagesInMemory.insert(page);
                pageFaults++;
            }
        }

        return pageFaults;
    }
};

int main() {
    // Hardcoded reference string and number of frames (memory size)
    vector<int> referenceString = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3};
    int numFrames = 3;  // Number of page frames in memory

    // Create an OptimalPageReplacement object with the given number of frames
    OptimalPageReplacement optimal(numFrames);

    // Calculate the number of page faults
    int pageFaults = optimal.calculatePageFaults(referenceString);

    // Output the result
    cout << "Number of page faults: " << pageFaults << endl;

    return 0;
}

/*
    Program Description:
    This C++ program simulates the **Optimal** page replacement algorithm to calculate 
    the number of page faults. The program uses an **unordered_set** to track pages 
    in memory and simulates the optimal page replacement strategy by replacing the 
    page that will not be used for the longest time in the future.

    FAQ Section:

    Q1: **What is the Optimal Page Replacement Algorithm?**
    A1: The **Optimal Page Replacement Algorithm** replaces the page that will not be used for the longest period of time in the future. 
       This algorithm minimizes the number of page faults, but it is not practical for real systems as it requires knowledge of future page accesses.

    Q2: **How does the Optimal Algorithm determine which page to replace?**
    A2: The Optimal Algorithm selects the page that will not be used for the longest period in the future. If a page is not referenced after a certain point in the reference string, it is the candidate for replacement.

    Q3: **How are page faults counted in this program?**
    A3: A **page fault** occurs whenever a process attempts to access a page that is not currently in memory. The program counts how many such page accesses occur while processing the reference string.

    Q4: **What happens when memory is full?**
    A4: When memory is full, the **Optimal Algorithm** replaces the page that will not be used for the longest time in the future.

    Q5: **Why is the Optimal Page Replacement Algorithm not used in real systems?**
    A5: The **Optimal Algorithm** requires future knowledge of page accesses, which is generally not available in real-world systems. Thus, other algorithms like **LRU (Least Recently Used)** or **FIFO (First In First Out)** are more commonly used.
*/



/* producerconsumermutex.cpp */

#include <iostream>
#include <pthread.h>        // For pthread functionality
#include <queue>            // For using the queue as a buffer
#include <unistd.h>         // For sleep() function
#include <mutex>            // For std::mutex
#include <condition_variable> // For condition_variable

using namespace std;

// Buffer size (number of items the buffer can hold)
#define BUFFER_SIZE 5

// Shared buffer (queue for storing items produced by producers)
queue<int> buffer;

// Mutex for mutual exclusion on buffer access
mutex mtx;

// Condition variables to synchronize producer and consumer threads
condition_variable cv_empty;  // Wait when buffer is full
condition_variable cv_full;   // Wait when buffer is empty

// Producer thread function
void* producer(void* arg) {
    int item = 0;  // Item produced by the producer
    
    while (true) {
        // Lock the mutex to safely access the buffer
        unique_lock<mutex> lock(mtx);

        // Wait until there is space in the buffer
        while (buffer.size() == BUFFER_SIZE) {
            cv_empty.wait(lock); // Wait if buffer is full
        }

        // Produce an item and add it to the buffer
        buffer.push(item);
        cout << "Producer " << pthread_self() << " produced item: " << item << endl;
        item++;  // Increment item for next production

        // Notify consumers that new items are available
        cv_full.notify_all();  // Notify consumers that the buffer has new data
        
        // Simulate production time
        sleep(1);
    }

    return nullptr;
}

// Consumer thread function
void* consumer(void* arg) {
    while (true) {
        // Lock the mutex to safely access the buffer
        unique_lock<mutex> lock(mtx);

        // Wait until the buffer is not empty
        while (buffer.empty()) {
            cv_full.wait(lock);  // Wait if buffer is empty
        }

        // Consume an item from the buffer
        int item = buffer.front();
        buffer.pop();
        cout << "Consumer " << pthread_self() << " consumed item: " << item << endl;

        // Notify producers that there is space in the buffer
        cv_empty.notify_all();  // Notify producers that the buffer has space

        // Simulate consumption time
        sleep(2);
    }

    return nullptr;
}

int main() {
    pthread_t producers[3], consumers[3];  // Arrays to store producer and consumer threads

    // Create producer threads
    for (int i = 0; i < 3; ++i) {
        if (pthread_create(&producers[i], nullptr, producer, nullptr) != 0) {
            cerr << "Failed to create producer thread!" << endl;
            return 1;
        }
    }

    // Create consumer threads
    for (int i = 0; i < 3; ++i) {
        if (pthread_create(&consumers[i], nullptr, consumer, nullptr) != 0) {
            cerr << "Failed to create consumer thread!" << endl;
            return 1;
        }
    }

    // Join all threads
    for (int i = 0; i < 3; ++i) {
        pthread_join(producers[i], nullptr);  // Wait for all producer threads to finish
    }
    for (int i = 0; i < 3; ++i) {
        pthread_join(consumers[i], nullptr);  // Wait for all consumer threads to finish
    }

    return 0;  // Successful execution
}

/*
    Program Description:
    This C++ program implements the Producer-Consumer problem using threads, mutexes, and condition variables. 
    The shared buffer is implemented using a queue, and the producer and consumer threads use synchronization 
    mechanisms to ensure proper interaction. The program simulates a system where multiple producers produce items 
    and add them to the buffer, while multiple consumers remove items from the buffer and process them.

    1. **Shared Buffer**:
        - The shared buffer is a queue (`buffer`) that stores the items produced by producers and consumed by consumers.
    
    2. **Thread Synchronization**:
        - A `mutex` (`mtx`) is used to ensure mutual exclusion, allowing only one thread to access the buffer at a time.
        - Two condition variables are used:
            - `cv_empty`: Notifies producer threads when space is available in the buffer.
            - `cv_full`: Notifies consumer threads when data is available in the buffer.

    3. **Producer Threads**:
        - Multiple producer threads generate items and add them to the buffer. If the buffer is full, they wait until there is space.

    4. **Consumer Threads**:
        - Multiple consumer threads consume items from the buffer. If the buffer is empty, they wait until there are items to consume.

    5. **Thread Execution**:
        - The program creates three producer threads and three consumer threads using `pthread_create()`.
        - It waits for all threads to complete using `pthread_join()`.

    FAQ Section:

    Q1: Why do we use `mutex` and `condition_variable` in this program?
    A1: The `mutex` ensures that only one thread can access the buffer at a time, providing mutual exclusion. The `condition_variable` is used to synchronize producers and consumers, allowing them to wait for appropriate conditions (e.g., waiting if the buffer is full or empty).

    Q2: What is the purpose of `cv_empty` and `cv_full` condition variables?
    A2: `cv_empty` is used by consumers to wait if the buffer is empty, and `cv_full` is used by producers to wait if the buffer is full. These condition variables help ensure that producers and consumers don't try to access the buffer when it's not appropriate.

    Q3: How does the producer know when to add an item to the buffer?
    A3: The producer checks if the buffer is full. If it is, the producer waits on the `cv_empty` condition variable until there is space in the buffer.

    Q4: What happens when the buffer is empty?
    A4: When the buffer is empty, consumer threads wait on the `cv_full` condition variable until producers add items to the buffer.

    Q5: What is the significance of `pthread_create()` and `pthread_join()` in this program?
    A5: `pthread_create()` is used to create producer and consumer threads, while `pthread_join()` is used to wait for these threads to complete their execution. This ensures that the main thread waits for all worker threads to finish.

    Q6: How can this approach be extended to larger systems with more producers or consumers?
    A6: The approach can be scaled by increasing the number of producer and consumer threads. The buffer size and synchronization mechanisms would remain the same, but the system could handle larger workloads by creating more threads.

    Q7: Can multiple producers and consumers work in parallel?
    A7: Yes, multiple producers and consumers can work in parallel. Producers add items to the buffer, and consumers remove them, with proper synchronization to ensure that they don't step on each other's toes.

    Q8: How is mutual exclusion handled for buffer access?
    A8: Mutual exclusion is handled using a `mutex`. Only one thread can access the buffer at a time (either a producer or a consumer), ensuring safe access to the shared resource.
*/



/* producerconsumersemaphore.cpp */

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <queue>
#include <unistd.h>  // For sleep()

using namespace std;

sem_t empty, full, mutex;  // Semaphores for buffer access
queue<int> buffer;         // Shared buffer
const int BUFFER_SIZE = 5; // Maximum buffer size

// Producer thread function
void* producer(void* arg) {
    int item = 0;  // Item produced by producer
    while (true) {
        sem_wait(&empty);   // Wait if the buffer is full
        sem_wait(&mutex);   // Lock the buffer

        // Produce an item and add to buffer
        buffer.push(item);
        cout << "Producer " << pthread_self() << " produced item: " << item << endl;
        item++;

        sem_post(&mutex);   // Unlock the buffer
        sem_post(&full);    // Notify consumer that buffer is not empty

        sleep(1);  // Simulate production time
    }

    return nullptr;
}

// Consumer thread function
void* consumer(void* arg) {
    while (true) {
        sem_wait(&full);    // Wait if the buffer is empty
        sem_wait(&mutex);   // Lock the buffer

        // Consume an item from the buffer
        int item = buffer.front();
        buffer.pop();
        cout << "Consumer " << pthread_self() << " consumed item: " << item << endl;

        sem_post(&mutex);   // Unlock the buffer
        sem_post(&empty);   // Notify producer that buffer has space

        sleep(2);  // Simulate consumption time
    }

    return nullptr;
}

int main() {
    pthread_t producers[3], consumers[3];  // Arrays to store producer and consumer threads

    sem_init(&empty, 0, BUFFER_SIZE);   // Initially buffer is empty
    sem_init(&full, 0, 0);              // Initially buffer is full
    sem_init(&mutex, 0, 1);             // Mutex for buffer access

    // Create producer threads
    for (int i = 0; i < 3; ++i) {
        pthread_create(&producers[i], nullptr, producer, nullptr);
    }

    // Create consumer threads
    for (int i = 0; i < 3; ++i) {
        pthread_create(&consumers[i], nullptr, consumer, nullptr);
    }

    // Join all threads
    for (int i = 0; i < 3; ++i) {
        pthread_join(producers[i], nullptr);
    }
    for (int i = 0; i < 3; ++i) {
        pthread_join(consumers[i], nullptr);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}

/*
    Program Description:
    This C++ program implements the Producer-Consumer problem using threads and semaphores. 
    The shared buffer is implemented using a queue, and the producer and consumer threads use synchronization 
    mechanisms to ensure proper interaction. The program simulates a system where multiple producers produce items 
    and add them to the buffer, while multiple consumers remove items from the buffer and process them.

    1. **Shared Buffer**:
        - The shared buffer is a queue (`buffer`) that stores the items produced by producers and consumed by consumers.
    
    2. **Thread Synchronization**:
        - A `mutex` (`mutex`) is used to ensure mutual exclusion when accessing the buffer.
        - Two condition variables are used:
            - `empty`: Notifies producer threads when space is available in the buffer.
            - `full`: Notifies consumer threads when data is available in the buffer.

    3. **Producer Threads**:
        - Multiple producer threads generate items and add them to the buffer. If the buffer is full, they wait until there is space.

    4. **Consumer Threads**:
        - Multiple consumer threads consume items from the buffer. If the buffer is empty, they wait until there are items to consume.

    5. **Thread Execution**:
        - The program creates three producer threads and three consumer threads using `pthread_create()`.
        - It waits for all threads to complete using `pthread_join()`.

    FAQ Section:

    Q1: **Why do we use semaphores in this program?**  
    A1: Semaphores are used to synchronize access to the shared buffer. The `empty` semaphore keeps track of available space in the buffer, while the `full` semaphore keeps track of how many items are in the buffer. The `mutex` semaphore ensures that only one thread accesses the buffer at a time, providing mutual exclusion.

    Q2: **What happens when the buffer is full?**  
    A2: When the buffer is full, the producer threads wait on the `empty` semaphore until there is space available in the buffer. The producer can only add items once there is space, and `empty` is incremented to signal this.

    Q3: **How do consumers wait if the buffer is empty?**  
    A3: When the buffer is empty, consumer threads wait on the `full` semaphore until producers add items to the buffer. The consumer can only consume items once there is data, and `full` is incremented to signal this.

    Q4: **What is the purpose of the `mutex` semaphore?**  
    A4: The `mutex` semaphore ensures that only one thread can access the buffer at a time. This prevents race conditions where both a producer and a consumer might try to modify the buffer simultaneously.

    Q5: **How do the producer and consumer threads communicate with each other?**  
    A5: Producer threads use the `empty` semaphore to check if there is space in the buffer, and consumers use the `full` semaphore to check if there is data available. Both semaphores help synchronize the two types of threads, ensuring that they do not interfere with each other.

    Q6: **Why is the `empty` semaphore initialized to `BUFFER_SIZE`?**  
    A6: The `empty` semaphore is initialized to `BUFFER_SIZE` because that is the maximum number of items the buffer can hold. This indicates that the buffer starts out with enough space for all items.

    Q7: **Why is the `full` semaphore initialized to 0?**  
    A7: The `full` semaphore is initialized to 0 because the buffer starts out empty. When producers add items, the `full` semaphore is incremented to signal that data is available for consumers to consume.

    Q8: **What happens when a producer finishes producing an item?**  
    A8: After a producer produces an item, it adds it to the buffer, releases the `mutex` to allow other threads to access the buffer, and increments the `full` semaphore to notify consumers that the buffer now has data.

    Q9: **How is deadlock avoided in this program?**  
    A9: Deadlock is avoided because the semaphores are properly initialized and used. The producer waits for space to become available in the buffer using the `empty` semaphore, and the consumer waits for data to become available using the `full` semaphore. The `mutex` semaphore ensures that only one thread can access the buffer at a time, preventing race conditions.

    Q10: **Can this program be scaled with more producers and consumers?**  
    A10: Yes, this program can be easily scaled by adding more producer and consumer threads. The semaphores and buffer size would need to be adjusted accordingly, but the logic will remain the same.
*/



/* readerwritemutex.cpp */

#include <iostream>
#include <pthread.h>  // For pthreads
#include <unistd.h>   // For sleep() function
#include <mutex>      // For std::mutex
#include <condition_variable> // For condition_variable

using namespace std;

// Shared resource
int sharedData = 0;  // Shared data accessed by readers and writers

// Mutexes and condition variables for synchronization
mutex mtx;                // Mutex to ensure mutual exclusion for writers
condition_variable cv;    // Condition variable for controlling access to sharedData
int readerCount = 0;      // Count of active readers

// Reader thread function
void* reader(void* arg) {
    unique_lock<mutex> lock(mtx);  // Lock the mutex for synchronization

    // Wait until no writer is active (this ensures multiple readers can access sharedData concurrently)
    while (readerCount == -1) {
        cv.wait(lock); // Wait if a writer is writing
    }

    // Increment reader count
    readerCount++;

    // Reading the shared data
    cout << "Reader " << pthread_self() << " is reading sharedData: " << sharedData << endl;

    // Simulate reading by sleeping for a short time
    sleep(1);

    // Decrement reader count and notify writers if no readers are left
    readerCount--;
    if (readerCount == 0) {
        cv.notify_all(); // Notify writers if no readers are left
    }

    return nullptr;
}

// Writer thread function
void* writer(void* arg) {
    unique_lock<mutex> lock(mtx);  // Lock the mutex to get exclusive access

    // If any readers are active, wait for them to finish
    while (readerCount > 0) {
        cv.wait(lock);  // Wait if there are active readers
    }

    // Indicate that a writer is now active (no readers can access the sharedData)
    readerCount = -1;

    // Writing to shared data
    sharedData++;  // Simple write operation: increment sharedData
    cout << "Writer " << pthread_self() << " is writing sharedData: " << sharedData << endl;

    // Simulate writing by sleeping for a short time
    sleep(1);

    // After writing, allow readers to access sharedData again
    readerCount = 0;
    cv.notify_all();  // Notify readers and other writers

    return nullptr;
}

int main() {
    pthread_t readers[5], writers[2];  // Arrays to store reader and writer threads

    // Create reader threads
    for (int i = 0; i < 5; ++i) {
        if (pthread_create(&readers[i], nullptr, reader, nullptr) != 0) {
            cerr << "Failed to create reader thread!" << endl;
            return 1;
        }
    }

    // Create writer threads
    for (int i = 0; i < 2; ++i) {
        if (pthread_create(&writers[i], nullptr, writer, nullptr) != 0) {
            cerr << "Failed to create writer thread!" << endl;
            return 1;
        }
    }

    // Join all threads
    for (int i = 0; i < 5; ++i) {
        pthread_join(readers[i], nullptr);  // Wait for all reader threads to finish
    }
    for (int i = 0; i < 2; ++i) {
        pthread_join(writers[i], nullptr);  // Wait for all writer threads to finish
    }

    return 0;  // Successful execution
}

/*
    Program Description:
    This C++ program implements the Reader-Writer problem using threads and mutexes. The problem 
    allows multiple readers to read shared data simultaneously, but only one writer can write to 
    the shared data at a time. The program uses mutexes to ensure mutual exclusion and synchronization.

    1. **Shared Resource**:
        - `sharedData` is the shared resource that both readers and writers access.
    
    2. **Thread Synchronization**:
        - A `mutex` (`mtx`) is used to ensure mutual exclusion when writing to `sharedData`.
        - A `condition_variable` (`cv`) is used to manage synchronization between readers and writers. It allows readers to wait if a writer is active and notifies them when writing is finished.

    3. **Reader Threads**:
        - Multiple readers can read `sharedData` simultaneously, but they must wait if any writer is active.
        - A counter (`readerCount`) is used to keep track of active readers. When no readers are active, writers can write to `sharedData`.

    4. **Writer Threads**:
        - Only one writer can write at a time, and writers must wait for all readers to finish before they can access `sharedData`.

    5. **Thread Execution**:
        - The program creates multiple reader and writer threads using `pthread_create()`.
        - The program waits for all threads to finish using `pthread_join()`.

    FAQ Section:

    Q1: What is the purpose of using `mutex` and `condition_variable` in this program?
    A1: The `mutex` ensures that only one writer can write to `sharedData` at a time, while the `condition_variable` is used to manage synchronization between readers and writers, ensuring that writers do not write when readers are active, and vice versa.

    Q2: What does the `readerCount` variable do?
    A2: The `readerCount` variable keeps track of how many readers are currently active. Writers wait until there are no active readers, and readers wait if a writer is writing.

    Q3: Why do we use `pthread_create()` and `pthread_join()`?
    A3: `pthread_create()` is used to create reader and writer threads, and `pthread_join()` is used to wait for all threads to finish execution. This ensures that the main program waits for all threads to complete before exiting.

    Q4: What happens if a writer tries to write while readers are active?
    A4: The writer will be blocked (i.e., it will wait) until all readers have finished reading. The condition variable is used to make the writer wait until there are no active readers.

    Q5: How does a reader know when it can start reading?
    A5: A reader checks if no writer is active. If any writer is writing, the reader will wait for the condition variable to be notified.

    Q6: Can multiple readers read simultaneously?
    A6: Yes, multiple readers can read simultaneously because reading does not modify `sharedData`. However, if any writer is active, all readers must wait.

    Q7: How is mutual exclusion achieved for writers?
    A7: Mutual exclusion for writers is achieved using the `mutex`. Only one writer can hold the mutex at a time, ensuring that no other writer or reader can access `sharedData` while the writer is writing.
*/



/* readerwritersemaphore.cpp */

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>  // For sleep()

using namespace std;

sem_t mutex, writeMutex;  // Mutex for writers and a general mutex for readers
int readCount = 0;        // Number of readers currently reading
int sharedData = 0;       // Shared data

// Reader thread function
void* reader(void* arg) {
    while (true) {
        sem_wait(&mutex);   // Enter critical section
        readCount++;
        if (readCount == 1) {
            sem_wait(&writeMutex);  // First reader locks the writer
        }
        sem_post(&mutex);   // Exit critical section

        // Reading the shared data
        cout << "Reader " << pthread_self() << " is reading: " << sharedData << endl;
        
        sleep(1);  // Simulate reading time

        sem_wait(&mutex);  // Enter critical section
        readCount--;
        if (readCount == 0) {
            sem_post(&writeMutex);  // Last reader unlocks the writer
        }
        sem_post(&mutex);  // Exit critical section
    }

    return nullptr;
}

// Writer thread function
void* writer(void* arg) {
    while (true) {
        sem_wait(&writeMutex);  // Lock for exclusive writing

        // Writing to shared data
        sharedData++;
        cout << "Writer " << pthread_self() << " is writing: " << sharedData << endl;

        sleep(2);  // Simulate writing time

        sem_post(&writeMutex);  // Unlock writer
    }

    return nullptr;
}

int main() {
    pthread_t readers[5], writers[2];

    sem_init(&mutex, 0, 1);       // Initialize mutex for readers
    sem_init(&writeMutex, 0, 1);  // Initialize write mutex for writers

    // Create reader threads
    for (int i = 0; i < 5; ++i) {
        pthread_create(&readers[i], nullptr, reader, nullptr);
    }

    // Create writer threads
    for (int i = 0; i < 2; ++i) {
        pthread_create(&writers[i], nullptr, writer, nullptr);
    }

    // Join all threads
    for (int i = 0; i < 5; ++i) {
        pthread_join(readers[i], nullptr);
    }
    for (int i = 0; i < 2; ++i) {
        pthread_join(writers[i], nullptr);
    }

    sem_destroy(&mutex);
    sem_destroy(&writeMutex);

    return 0;
}

/*
    Program Description:
    This C++ program implements the Reader-Writer problem using threads and semaphores. The problem 
    allows multiple readers to access the shared resource simultaneously, but only one writer can access 
    it at a time. The program uses semaphores to synchronize access to the shared resource.

    1. **Shared Resource**:
        - `sharedData` is the shared resource that both readers and writers access.
    
    2. **Thread Synchronization**:
        - A `mutex` (`mutex`) is used to ensure mutual exclusion when accessing the reader count.
        - A `writeMutex` semaphore is used to allow only one writer to access `sharedData` at a time.
    
    3. **Reader Threads**:
        - Multiple readers can read `sharedData` simultaneously, but they must wait if a writer is writing.
        - A counter (`readCount`) is used to track how many readers are currently reading. The first reader locks the writer, and the last reader unlocks it.

    4. **Writer Threads**:
        - Only one writer can write to `sharedData` at a time. Writers wait for all readers to finish before accessing `sharedData`.

    5. **Thread Execution**:
        - The program creates multiple reader and writer threads using `pthread_create()`.
        - It waits for all threads to finish using `pthread_join()`.

    FAQ Section:

    Q1: **Why are semaphores used in this problem?**  
    A1: Semaphores are used to synchronize the readers and writers. A `writeMutex` is used to ensure that only one writer can write at a time. A `mutex` for readers is used to keep track of how many readers are currently reading. This ensures that multiple readers can access the shared resource simultaneously, but no readers can read while a writer is writing.

    Q2: **How do semaphores ensure mutual exclusion in the Reader-Writer problem?**  
    A2: The `writeMutex` ensures that when one writer is writing, no other writers or readers can access the shared resource. The `mutex` protects the reader count, which helps prevent a situation where one writer would write while some readers are still active.

    Q3: **How does a writer gain access to the shared resource?**  
    A3: The writer must wait for all readers to finish by waiting for the `writeMutex`. If there are no active readers, the writer can gain exclusive access to the shared resource, incrementing the shared data and writing it. After the writer is done, it releases the `writeMutex`.

    Q4: **Why does the first reader lock the writer?**  
    A4: The first reader locks the `writeMutex` to ensure that writers cannot access the shared resource while any readers are reading. This prevents a situation where a writer would try to write while readers are accessing the shared data.

    Q5: **Can multiple readers access the shared resource at the same time?**  
    A5: Yes, multiple readers can access the shared resource concurrently. However, if a writer is active, readers must wait for the writer to finish.

    Q6: **What happens when a writer finishes writing?**  
    A6: Once a writer has finished writing, it releases the `writeMutex`, allowing readers to access the shared resource again.

    Q7: **What happens if multiple writers try to write at the same time?**  
    A7: Only one writer can access the shared resource at a time, thanks to the `writeMutex`. If multiple writers attempt to write, they must wait for the mutex to be released by the current writer before proceeding.

    Q8: **How are deadlocks prevented in this solution?**  
    A8: Deadlocks are prevented because the mutex and `writeMutex` semaphores are used with specific conditions. Readers can read simultaneously but only if no writers are active. Writers wait for readers to finish, and readers don't lock the writer semaphore unless they are the first one.

    Q9: **How does the `readCount` variable work?**  
    A9: The `readCount` variable keeps track of the number of active readers. It is incremented each time a reader starts reading and decremented when a reader finishes. If the first reader starts, it locks the `writeMutex`, and when the last reader finishes, it releases the lock, allowing writers to access the shared resource.

    Q10: **How does the program handle multiple threads?**  
    A10: The program creates multiple reader and writer threads using `pthread_create()`. Each thread is executed independently but is synchronized through the semaphores to prevent conflicting access to the shared resource.

    Q11: **How can this program be modified to support more readers and writers?**  
    A11: The program can be scaled by simply creating more reader and writer threads. The semaphore synchronization mechanisms will handle the increased load, ensuring mutual exclusion and preventing conflicts between readers and writers.

    Q12: **What are the limitations of this approach?**  
    A12: While this approach works well for managing readers and writers, it may suffer from starvation if writers keep being blocked by a continuous stream of readers. One way to address this is by implementing a writer-preference or reader-preference system, but that would require additional logic and more complex synchronization.

*/



/* scandisk.cpp */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

class SCAN {
private:
    vector<int> requests;  // Vector to store the disk requests
    int initialPosition;   // Initial position of the disk arm
    int diskSize;          // Total size of the disk (maximum possible track number)

public:
    // Constructor to initialize requests, initial position, and disk size
    SCAN(vector<int>& reqs, int initialPos, int size) : requests(reqs), initialPosition(initialPos), diskSize(size) {}

    // Function to simulate SCAN disk scheduling and calculate total seek time
    int calculateSeekTime(bool direction) {
        int totalSeekTime = 0;
        int currentPosition = initialPosition;  // Set initial position to current position

        vector<int> left, right;

        // Divide requests into left and right of the initial position
        for (int request : requests) {
            if (request < currentPosition) {
                left.push_back(request);
            } else {
                right.push_back(request);
            }
        }

        // Sort the requests in ascending order
        sort(left.begin(), left.end());
        sort(right.begin(), right.end());

        // If the direction is true, go towards the right, else go towards the left
        if (direction) {
            // Process the right side first
            totalSeekTime += abs(currentPosition - right.back());  // Move to the rightmost request
            currentPosition = right.back();

            // Serve requests on the right side
            for (int req : right) {
                totalSeekTime += abs(currentPosition - req);
                currentPosition = req;
            }

            // Reverse direction
            totalSeekTime += abs(currentPosition - left.front());  // Move to the leftmost request
            currentPosition = left.front();

            // Serve requests on the left side
            for (int req : left) {
                totalSeekTime += abs(currentPosition - req);
                currentPosition = req;
            }
        } else {
            // Process the left side first
            totalSeekTime += abs(currentPosition - left.front());  // Move to the leftmost request
            currentPosition = left.front();

            // Serve requests on the left side
            for (int req : left) {
                totalSeekTime += abs(currentPosition - req);
                currentPosition = req;
            }

            // Reverse direction
            totalSeekTime += abs(currentPosition - right.back());  // Move to the rightmost request
            currentPosition = right.back();

            // Serve requests on the right side
            for (int req : right) {
                totalSeekTime += abs(currentPosition - req);
                currentPosition = req;
            }
        }

        return totalSeekTime;
    }

    // Function to print the results in tabular format
    void printResults(bool direction) {
        cout << "\nSCAN Disk Scheduling Algorithm\n";
        cout << "---------------------------------\n";
        cout << "Initial Position of the Disk Arm: " << initialPosition << endl;
        cout << "Disk Size: " << diskSize << endl;
        cout << "Disk Requests: ";

        // Print the request sequence
        for (int i = 0; i < requests.size(); i++) {
            cout << requests[i] << " ";
        }
        cout << endl;

        // Calculate and print the total seek time
        int totalSeekTime = calculateSeekTime(direction);
        cout << "Total Seek Time: " << totalSeekTime << endl;

        // Print the table of movement
        cout << "\nDisk Scheduling (SCAN):\n";
        cout << "Current Position -> Request -> Seek Time\n";
        int currentPosition = initialPosition;
        int seekTime = 0;

        vector<int> left, right;

        // Divide requests into left and right of the initial position
        for (int request : requests) {
            if (request < currentPosition) {
                left.push_back(request);
            } else {
                right.push_back(request);
            }
        }

        // Sort the requests in ascending order
        sort(left.begin(), left.end());
        sort(right.begin(), right.end());

        if (direction) {
            // Process the right side first
            seekTime = abs(currentPosition - right.back());
            cout << setw(14) << currentPosition << setw(12) << right.back() << setw(14) << seekTime << endl;
            currentPosition = right.back();

            // Serve requests on the right side
            for (int req : right) {
                seekTime = abs(currentPosition - req);
                cout << setw(14) << currentPosition << setw(12) << req << setw(14) << seekTime << endl;
                currentPosition = req;
            }

            // Reverse direction
            seekTime = abs(currentPosition - left.front());
            cout << setw(14) << currentPosition << setw(12) << left.front() << setw(14) << seekTime << endl;
            currentPosition = left.front();

            // Serve requests on the left side
            for (int req : left) {
                seekTime = abs(currentPosition - req);
                cout << setw(14) << currentPosition << setw(12) << req << setw(14) << seekTime << endl;
                currentPosition = req;
            }
        } else {
            // Process the left side first
            seekTime = abs(currentPosition - left.front());
            cout << setw(14) << currentPosition << setw(12) << left.front() << setw(14) << seekTime << endl;
            currentPosition = left.front();

            // Serve requests on the left side
            for (int req : left) {
                seekTime = abs(currentPosition - req);
                cout << setw(14) << currentPosition << setw(12) << req << setw(14) << seekTime << endl;
                currentPosition = req;
            }

            // Reverse direction
            seekTime = abs(currentPosition - right.back());
            cout << setw(14) << currentPosition << setw(12) << right.back() << setw(14) << seekTime << endl;
            currentPosition = right.back();

            // Serve requests on the right side
            for (int req : right) {
                seekTime = abs(currentPosition - req);
                cout << setw(14) << currentPosition << setw(12) << req << setw(14) << seekTime << endl;
                currentPosition = req;
            }
        }

        cout << "\nTotal Seek Time: " << totalSeekTime << endl;
    }
};

int main() {
    // Hardcoded disk requests, initial position of the disk arm, and disk size
    vector<int> requests = {98, 183, 37, 122, 14, 124, 65, 67};
    int initialPosition = 53;
    int diskSize = 200;  // Total size of the disk (maximum possible track number)

    // Create SCAN object
    SCAN scan(requests, initialPosition, diskSize);

    // Print results and seek time (direction true = right, false = left)
    scan.printResults(true);  // Try with direction as 'true' (right)

    return 0;
}

/*
    Program Description:
    This C++ program simulates the **SCAN (Elevator)** disk scheduling algorithm. The program calculates 
    the total seek time and prints the input requests and corresponding output in a tabular format.

    The program calculates the page faults for a given reference string and outputs the number of page faults.

    FAQ Section:

    Q1: **What is SCAN disk scheduling?**
    A1: **SCAN (Elevator)** disk scheduling algorithm moves the disk arm towards one end of the disk and services 
       requests along the way. Once it reaches the end, it reverses direction and starts servicing requests in the opposite direction.

    Q2: **How is the seek time calculated?**
    A2: **Seek Time** is the absolute difference between the current position of the disk arm and the requested position. 
       The total seek time is the sum of the seek times for each request.

    Q3: **What happens when the disk arm reaches the end?**
    A3: When the disk arm reaches the end, it reverses direction and starts servicing the requests in the opposite direction.

    Q4: **Is SCAN optimal?**
    A4: SCAN minimizes the travel distance compared to **FCFS** and is generally more efficient. However, it may still cause some waiting time for requests on the opposite end if the disk arm is far away from them.

    Q5: **What are the disadvantages of SCAN?**
    A5: One of the disadvantages is that requests at the far end might experience significant waiting time, especially if they are serviced last during the scan.
*/



/* shellarmstrong.cpp */

#!/bin/bash

# Hardcoded number
num=153

# Initialize variables
sum=0
temp_num=$num
num_digits=${#num}  # Get the number of digits in the number

# Loop to calculate the sum of each digit raised to the power of the number of digits
while [ $temp_num -gt 0 ]
do
  # Extract the last digit
  digit=$(( temp_num % 10 ))

  # Add the digit raised to the power of the number of digits
  sum=$(( sum + digit ** num_digits ))

  # Remove the last digit from the number
  temp_num=$(( temp_num / 10 ))
done

# Check if the sum is equal to the original number
if [ $sum -eq $num ]; then
    echo "$num is an Armstrong number."
else
    echo "$num is not an Armstrong number."
fi

# FAQ:
# Q1: What is an Armstrong number?
# A1: An **Armstrong number** is a number that is equal to the sum of its own digits, each raised to the power of the number of digits.
#
# Q2: Can I change the number?
# A2: Yes, you can modify the value of the `num` variable to check other numbers.
#
# Q3: How does the script check for an Armstrong number?
# A3: The script calculates the sum of each digit raised to the power of the number of digits and compares it with the original number.
#
# Q4: What happens if the number is single-digit?
# A4: A single-digit number is always an Armstrong number because the sum of its digits raised to the power of 1 is the number itself.
#
# Q5: Can this script handle large numbers?
# A5: Yes, the script works for any integer, but for very large numbers, you might run into performance issues or integer overflow with very large exponents.



/* shellbubblesort.cpp */

#!/bin/bash

# Hardcoded array of numbers to be sorted
arr=(64 34 25 12 22 11 90)

# Function to perform Bubble Sort
bubbleSort() {
  local n=${#arr[@]}  # Get the length of the array
  # Outer loop for each pass
  for ((i = 0; i < n-1; i++))
  do
    # Inner loop for comparing adjacent elements
    for ((j = 0; j < n-i-1; j++))
    do
      # If the element is greater than the next element, swap them
      if [ ${arr[j]} -gt ${arr[$((j+1))]} ]; then
        # Swap the elements
        temp=${arr[j]}
        arr[$j]=${arr[$((j+1))]}
        arr[$((j+1))]=$temp
      fi
    done
  done
}

# Print the original array
echo "Original Array: ${arr[@]}"

# Call the bubbleSort function
bubbleSort

# Print the sorted array
echo "Sorted Array: ${arr[@]}"

# FAQ:
# Q1: What is Bubble Sort?
# A1: Bubble Sort is a simple comparison-based sorting algorithm where adjacent elements are compared and swapped if necessary. 
#     The process is repeated until the array is sorted.
#
# Q2: How does Bubble Sort work?
# A2: It repeatedly compares adjacent elements and swaps them if they are in the wrong order. After each pass through the list, 
#     the largest unsorted element "bubbles up" to its correct position.
#
# Q3: Is Bubble Sort efficient?
# A3: Bubble Sort has a time complexity of O(n^2) in the worst case, which makes it inefficient for large datasets.
#
# Q4: Can I change the array to sort other numbers?
# A4: Yes, you can modify the array in the script (the `arr` variable) to sort different numbers.
#
# Q5: What happens if the array is already sorted?
# A5: If the array is already sorted, Bubble Sort still goes through all the iterations, making it inefficient compared to more optimized algorithms.



/* shellfactorial.cpp */

#!/bin/bash

# Hardcoded number for which we want to calculate the factorial
num=5

# Initialize the variable factorial to 1 (the base value for multiplication)
factorial=1

# Loop through the numbers from 1 to the hardcoded number
for (( i=1; i<=num; i++ ))
do
  # Multiply factorial by the current loop number
  factorial=$(( factorial * i ))
done

# Output the result of the factorial calculation
echo "The factorial of $num (non-recursive) is $factorial"

# FAQ:
# Q1: What does this script do?
# A1: This script calculates the factorial of the number 5 using an iterative (non-recursive) method with a for loop.
#
# Q2: How does the iterative factorial calculation work?
# A2: The loop multiplies the `factorial` variable by each integer from 1 to the given number. The result is the factorial.
#
# Q3: Can I change the number?
# A3: Yes, you can change the value of the `num` variable to any positive integer to calculate its factorial.
#
# Q4: What will happen if I set num to 0 or 1?
# A4: The script will still work, as the factorial of 0 and 1 is always 1.



// NEW SECTION //


#!/bin/bash

# Hardcoded number for which we want to calculate the factorial
num=5

# Recursive function to calculate the factorial
factorial() {
  # Base case: if the input is 1 or 0, return 1
  if [ $1 -le 1 ]; then
    echo 1
  else
    # Recursive case: n * factorial(n-1)
    prev=$(factorial $(( $1 - 1 )))  # Recursively call the factorial function with (n-1)
    echo $(( $1 * prev ))  # Multiply the current number with the result of the recursive call
  fi
}

# Calling the recursive function to calculate the factorial
result=$(factorial $num)

# Output the result of the factorial calculation
echo "The factorial of $num (recursive) is $result"

# FAQ:
# Q1: What does this script do?
# A1: This script calculates the factorial of the number 5 using a recursive method.
#
# Q2: How does recursion work in this script?
# A2: The function calls itself repeatedly, each time with a smaller number, until it reaches the base case where n <= 1.
#     Then it starts returning the results, multiplying each number with the previous result.
#
# Q3: Can I change the number?
# A3: Yes, you can change the value of the `num` variable to any positive integer to calculate its factorial.
#
# Q4: What will happen if I set num to 0 or 1?
# A4: The base case of the recursive function handles both `num = 0` and `num = 1`, returning a factorial value of 1.
#
# Q5: Is recursion more efficient than iteration in this case?
# A5: Recursion may consume more memory due to the call stack, and in some cases, iteration (non-recursive) can be more efficient.




/* shelloccurences.cpp */

#!/bin/bash

# Hardcoded string and substring
string="hello world, hello everyone, hello universe"
substring="hello"

# Method 1: Using 'grep' to count occurrences
count1=$(echo "$string" | grep -o "$substring" | wc -l)

# Method 2: Using Bash parameter expansion to count occurrences
count2=0
temp_string="$string"
while [[ "$temp_string" == *"$substring"* ]]; do
    count2=$((count2 + 1))
    temp_string="${temp_string#*$substring}"  # Remove the first occurrence of substring
done

# Output the results
echo "Method 1: The substring '$substring' occurred $count1 times (using 'grep')."
echo "Method 2: The substring '$substring' occurred $count2 times (using bash expansion)."

# FAQ:
# Q1: What does the script do?
# A1: This script counts how many times the substring `hello` appears in the string `hello world, hello everyone, hello universe`.
#     It uses two different methods: `grep` and bash parameter expansion.
#
# Q2: Can I change the string or substring?
# A2: Yes, you can modify the values of `string` and `substring` to check for different strings and substrings.
#
# Q3: What is the `grep` method doing?
# A3: The `grep -o` command finds all occurrences of the substring in the string. The `-o` option makes `grep` output 
#     each match on a new line, and `wc -l` counts how many lines were printed, which is equal to the number of matches.
#
# Q4: How does the bash parameter expansion method work?
# A4: In this method, the script repeatedly removes the first occurrence of the substring from the string, and each time it removes 
#     an occurrence, it increments the counter. The loop continues until no more occurrences are found.



/* shellpalindromenumber.cpp */

/*

#!/bin/bash

# Hardcoded number
num=121

# Reverse the number
original_num=$num
reverse_num=0

while [ $num -gt 0 ]
do
    remainder=$(( num % 10 ))  # Get the last digit
    reverse_num=$(( reverse_num * 10 + remainder ))  # Append the digit to reverse_num
    num=$(( num / 10 ))  # Remove the last digit from num
done

# Check if the original number is equal to the reversed number
if [ $original_num -eq $reverse_num ]; then
    echo "$original_num is a palindrome number."
else
    echo "$original_num is not a palindrome number."
fi

# FAQ:
# Q1: What does this script do?
# A1: This script checks if a hardcoded number is a palindrome by reversing the digits and comparing it with the original number.
#
# Q2: Can I change the number?
# A2: Yes, you can modify the `num` variable to any positive integer to check if it's a palindrome.
#
# Q3: What happens if the number is negative?
# A3: The script only checks positive integers. You can add additional checks to handle negative numbers if needed.
#
# Q4: How does the reversal process work?
# A4: The script extracts the last digit of the number using modulo (`% 10`), then constructs the reversed number by multiplying the existing reversed number by 10 and adding the extracted digit.
#
# Q5: Will this script work for multi-digit numbers?
# A5: Yes, the script works for any positive integer, regardless of the number of digits.

*/



/* shellpalindromestring.cpp */

/*
#!/bin/bash

# Hardcoded string
str="madam"

# Reverse the string
reverse_str=$(echo $str | rev)

# Check if the original string is equal to the reversed string
if [ "$str" == "$reverse_str" ]; then
    echo "\"$str\" is a palindrome string."
else
    echo "\"$str\" is not a palindrome string."
fi

# FAQ:
# Q1: What does this script do?
# A1: This script checks if a hardcoded string is a palindrome by reversing the string and comparing it with the original string.
#
# Q2: Can I change the string?
# A2: Yes, you can modify the `str` variable to any string to check if it's a palindrome.
#
# Q3: Does the script handle spaces and punctuation?
# A3: No, this script only checks the exact string. If you want to ignore spaces or punctuation, you would need to preprocess the string (e.g., removing spaces and non-alphabetic characters).
#
# Q4: How does the reversal process work?
# A4: The script uses the `rev` command to reverse the string. This command reads the string and outputs it in reverse order.
#
# Q5: Does the script handle case sensitivity?
# A5: Yes, the script is case-sensitive. To make it case-insensitive, you can convert both strings to lowercase using `tr` or `awk` before comparison.

*/



/* shellreversedigit.cpp */

/*
#!/bin/bash

# Hardcoded number
num=12345

# Initialize the reverse number to 0
reverse=0

# Loop to reverse the digits
while [ $num -gt 0 ]
do
  # Extract the last digit
  digit=$(( num % 10 ))

  # Append the digit to the reverse number
  reverse=$(( reverse * 10 + digit ))

  # Remove the last digit from the original number
  num=$(( num / 10 ))
done

# Output the result
echo "The reversed number is: $reverse"

# FAQ:
# Q1: What does this script do?
# A1: This script reverses the digits of the hardcoded number `12345`. It extracts each digit and adds it to the reversed number.
#
# Q2: Can I change the number?
# A2: Yes, you can modify the value of `num` to any integer you want to reverse the digits of that number.
#
# Q3: How does the script reverse the digits?
# A3: The script extracts the last digit of the number using modulo (`% 10`) and appends it to the reversed number by multiplying the reversed number by 10 and adding the extracted digit.
#
# Q4: What happens if the number is zero?
# A4: If the number is `0`, the reversed number will also be `0`.
#
# Q5: Can this script handle negative numbers?
# A5: This script does not handle negative numbers. You can add a check to handle negative numbers if required.

*/




/* sstfdisk.cpp */

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <climits>
using namespace std;

class SSTF {
private:
    vector<int> requests;  // Vector to store the disk requests
    int initialPosition;   // Initial position of the disk arm

public:
    // Constructor to initialize requests and initial position
    SSTF(vector<int>& reqs, int initialPos) : requests(reqs), initialPosition(initialPos) {}

    // Function to simulate SSTF disk scheduling and calculate total seek time
    int calculateSeekTime() {
        int totalSeekTime = 0;
        int currentPosition = initialPosition;  // Set initial position to current position

        vector<int> remainingRequests = requests;  // Create a copy of the requests to manipulate

        while (!remainingRequests.empty()) {
            // Find the closest request
            int minSeekTime = INT_MAX;
            int closestRequest = -1;
            int closestIndex = -1;

            for (int i = 0; i < remainingRequests.size(); i++) {
                int seekTime = abs(currentPosition - remainingRequests[i]);
                if (seekTime < minSeekTime) {
                    minSeekTime = seekTime;
                    closestRequest = remainingRequests[i];
                    closestIndex = i;
                }
            }

            // Add the seek time to the total seek time
            totalSeekTime += minSeekTime;

            // Move the disk arm to the closest request
            currentPosition = closestRequest;

            // Remove the processed request
            remainingRequests.erase(remainingRequests.begin() + closestIndex);
        }

        return totalSeekTime;
    }

    // Function to print the results in tabular format
    void printResults() {
        cout << "\nSSTF Disk Scheduling Algorithm\n";
        cout << "---------------------------------\n";
        cout << "Initial Position of the Disk Arm: " << initialPosition << endl;
        cout << "Disk Requests: ";

        // Print the request sequence
        for (int i = 0; i < requests.size(); i++) {
            cout << requests[i] << " ";
        }
        cout << endl;

        // Calculate and print the total seek time
        int totalSeekTime = calculateSeekTime();
        cout << "Total Seek Time: " << totalSeekTime << endl;

        // Print the table of movement
        cout << "\nDisk Scheduling (SSTF):\n";
        cout << "Current Position -> Request -> Seek Time\n";
        int currentPosition = initialPosition;
        int seekTime = 0;

        vector<int> remainingRequests = requests;  // Create a copy of the requests to manipulate
        while (!remainingRequests.empty()) {
            int minSeekTime = INT_MAX;
            int closestRequest = -1;
            int closestIndex = -1;

            for (int i = 0; i < remainingRequests.size(); i++) {
                seekTime = abs(currentPosition - remainingRequests[i]);
                if (seekTime < minSeekTime) {
                    minSeekTime = seekTime;
                    closestRequest = remainingRequests[i];
                    closestIndex = i;
                }
            }

            cout << setw(14) << currentPosition << setw(12) << closestRequest << setw(14) << minSeekTime << endl;
            currentPosition = closestRequest;
            remainingRequests.erase(remainingRequests.begin() + closestIndex);
        }

        cout << "\nTotal Seek Time: " << totalSeekTime << endl;
    }
};

int main() {
    // Hardcoded disk requests and initial position of the disk arm
    vector<int> requests = {98, 183, 37, 122, 14, 124, 65, 67};
    int initialPosition = 53;

    // Create SSTF object
    SSTF sstf(requests, initialPosition);

    // Print results and seek time
    sstf.printResults();

    return 0;
}

/*
    Program Description:
    This C++ program simulates the **SSTF (Shortest Seek Time First)** disk scheduling algorithm. 
    It calculates the total seek time and prints the input requests and corresponding output in a tabular format.

    The program calculates the page faults for a given reference string and outputs the number of page faults.

    FAQ Section:

    Q1: **What is the SSTF disk scheduling algorithm?**
    A1: **SSTF (Shortest Seek Time First)** disk scheduling algorithm selects the request that is closest to the current position of the disk arm. It minimizes the seek time by always choosing the closest request.

    Q2: **How is the seek time calculated?**
    A2: **Seek Time** is the absolute difference between the current position of the disk arm and the requested position. The total seek time is the sum of the seek times for each request.

    Q3: **What happens when a disk request is served?**
    A3: Once a request is served, the disk arm moves to the requested track, and the next closest request is processed.

    Q4: **Is SSTF optimal?**
    A4: SSTF minimizes seek time compared to **FCFS**, but it may lead to **starvation** for some requests if the disk arm keeps serving nearby requests and never moves to distant requests.

    Q5: **What is the main limitation of SSTF?**
    A5: The main limitation of **SSTF** is **starvation**. If a process continuously makes requests that are far away from the current disk arm position, it might never get serviced.
*/



/* systemcalls.cpp */

#include <iostream>
#include <unistd.h>        // For system calls like fork(), getpid(), getppid(), alarm(), etc.
#include <sys/types.h>     // For pid_t and other data types
#include <sys/wait.h>      // For wait()
#include <ctime>           // For time-related functions like gettimeofday()
#include <cstring>         // For strerror() and error handling
#include <errno.h>         // For error number definitions
#include <signal.h>        // For alarm() and signal handling

using namespace std;

int main() {
    pid_t pid;

    // Demonstrating getpid() system call to get the process ID
    pid_t process_id = getpid();
    cout << "Process ID: " << process_id << endl;

    // Demonstrating getppid() system call to get the parent process ID
    pid_t parent_process_id = getppid();
    cout << "Parent Process ID: " << parent_process_id << endl;

    // Demonstrating gettimeofday() to get the current time
    //struct timeval tv;
  // gettimeofday(&tv, NULL);
   // cout << "Current time: " << tv.tv_sec << " seconds and " << tv.tv_usec << " microseconds since the Epoch" << endl;

    // Creating a child process with fork()
    pid = fork(); 
    if (pid < 0) {
        cerr << "Fork failed: " << strerror(errno) << endl;
        return 1; // Exit with error
    }
    else if (pid == 0) {
        // Child process block

        // Using getpid() again in the child process
        cout << "Child Process ID (from child): " << getpid() << endl;
        
        // Using getppid() in the child process (getting the parent process ID)
        cout << "Parent Process ID (from child): " << getppid() << endl;

        // Using alarm() system call to set a timer for 5 seconds
        cout << "Child process sets an alarm to go off in 5 seconds." << endl;
        alarm(5); // Set an alarm for 5 seconds
        
        // Simulate some activity before alarm goes off
        cout << "Child process is doing some work..." << endl;

        // Wait for the alarm to signal (handled by signal handling mechanism, but just an illustration)
        // Here, the program will continue and terminate without waiting explicitly for the alarm

        // Using exit() to terminate the child process
        exit(0); // This will terminate the child process
    }
    else {
        // Parent process block

        // The parent process waits for the child to terminate
        int status;
        wait(&status); // Wait for child process to terminate

        // If the child process terminated normally
        if (WIFEXITED(status)) {
            cout << "Child process exited with status " << WEXITSTATUS(status) << endl;
        }
        else {
            cout << "Child process did not terminate normally." << endl;
        }

        // The parent can perform some additional work, if necessary
        cout << "Parent process completes execution." << endl;
    }

    return 0; // Successful execution
}

/*
    Program Description:
    This C++ program demonstrates the use of various system calls commonly used in UNIX-based systems. 
    It performs the following operations:
    
    1. **Process Creation and Management:**
        - Uses `fork()` to create a child process.
        - In the child process, it uses `getpid()` to get the child’s process ID, and `getppid()` to get the parent’s process ID.
        - The child process sets an alarm using `alarm()` to go off in 5 seconds and continues execution.
        - The parent process waits for the child process to terminate using `wait()`.
    
    2. **Time Operations:**
        - Uses `gettimeofday()` to display the current time (in seconds and microseconds).
    
    3. **Process Termination:**
        - The child process terminates using `exit(0)`.
    
    The program demonstrates basic system call usage like `getpid()`, `getppid()`, `alarm()`, `wait()`, and `gettimeofday()`. It also shows process creation with `fork()` and termination with `exit()`. The program is entirely hard-coded and does not require any user input. Detailed comments are provided for each line to explain the functionality.

    FAQ Section:

    Q1: What is the `getpid()` system call used for?
    A1: `getpid()` returns the process ID of the calling process. It is useful for identifying the current process in a multi-process environment.

    Q2: How is `getppid()` different from `getpid()`?
    A2: `getppid()` returns the process ID of the parent of the calling process, while `getpid()` returns the ID of the current process.

    Q3: What does the `fork()` system call do?
    A3: `fork()` creates a new process by duplicating the current process. It returns 0 in the child process and the child's process ID in the parent process.

    Q4: What is the purpose of the `wait()` system call?
    A4: `wait()` is used by the parent process to wait for the child process to terminate. It allows the parent to obtain the exit status of the child.

    Q5: What does `exit()` do?
    A5: `exit()` terminates the current process and optionally provides an exit status to the parent process. The status is used to indicate whether the process terminated successfully or with an error.

    Q6: How does `alarm()` work in the program?
    A6: The `alarm()` system call sets an alarm for a specified number of seconds. When the timer expires, a signal (SIGALRM) is sent to the process. This is a simple demonstration and doesn't handle the signal explicitly.

    Q7: What does `gettimeofday()` do?
    A7: `gettimeofday()` gets the current time with microsecond precision. It returns the time elapsed since the Unix Epoch (January 1, 1970) in seconds and microseconds.

    Q8: Why is `exit()` used in the child process?
    A8: `exit()` is used to terminate the child process gracefully. It sends an exit status to the parent process, allowing the parent to determine how the child terminated.
*/



/* zombie.cpp */

#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

using namespace std;

void calculateEvenSum(const vector<int>& arr) {
    int sum = 0;
    for (int num : arr) {
        if (num % 2 == 0) {
            sum += num;
        }
    }
    cout << "Sum of even numbers in the array (Parent Process): " << sum << endl;
}

void calculateOddSum(const vector<int>& arr) {
    int sum = 0;
    for (int num : arr) {
        if (num % 2 != 0) {
            sum += num;
        }
    }
    cout << "Sum of odd numbers in the array (Child Process): " << sum << endl;
}

int main() {
    // Sample array
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Creating a child process using fork()
    pid_t pid = fork();

    if (pid == -1) {
        // Fork failed
        cerr << "Fork failed!" << endl;
        return 1;
    } else if (pid == 0) {
        // This is the child process
        calculateOddSum(arr);

        // Simulate a Zombie Process by terminating without parent calling wait()
        // The child process terminates, and the parent process has not yet called wait
        cout << "Child process is terminating, becoming a Zombie process!" << endl;
        _exit(0);
    } else {
        // This is the parent process
        calculateEvenSum(arr);

        // Simulate Orphan Process by terminating before the child process
        // Parent process terminates before the child has a chance to terminate
        cout << "Parent process is terminating, leaving the child process as orphan!" << endl;
        sleep(2); // Sleep to allow child process to execute and become orphaned

        // Wait for child process to avoid Zombie process
        wait(nullptr);

        cout << "Parent process has terminated." << endl;
    }

    return 0;
}

/*
    Program Description:
    This C++ program demonstrates:
    1. **Zombie Process**: A child process terminates, but the parent has not yet called `wait()` to collect the exit status, resulting in a zombie process.
    2. **Orphan Process**: The child process becomes an orphan after the parent terminates first, and `init` becomes the parent.
    3. **Sum of Even and Odd Numbers**: The program calculates the sum of even numbers in the array in the parent process, and the sum of odd numbers in the child process.

    FAQ Section:

    Q1: **What is a Zombie Process?**
    A1: A **Zombie Process** is a process that has completed execution but still has an entry in the process table. This occurs when the parent process has not called `wait()` to read the exit status of the child process.

    Q2: **What is an Orphan Process?**
    A2: An **Orphan Process** is a child process whose parent has terminated. In this case, the `init` process (process ID 1) becomes the new parent.

    Q3: **What happens when the parent terminates before the child?**
    A3: If the parent process terminates before the child process, the child becomes an orphan and is adopted by the `init` process.

    Q4: **How is the sum of even and odd numbers calculated in the program?**
    A4: The **parent process** calculates the sum of even numbers in the array, while the **child process** calculates the sum of odd numbers in the array. Each process is responsible for one part of the task, which is executed concurrently.

    Q5: **How do we simulate a Zombie process in the program?**
    A5: The child process terminates (`_exit(0)`) before the parent has a chance to call `wait()`, simulating a zombie process.

    Q6: **How does the parent process cause the child to become orphaned?**
    A6: The parent process terminates before the child has a chance to terminate, making the child an orphan. The operating system then assigns the `init` process as the parent of the orphaned child.
*/