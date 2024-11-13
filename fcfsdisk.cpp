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
