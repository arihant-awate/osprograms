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
