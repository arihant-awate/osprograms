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
