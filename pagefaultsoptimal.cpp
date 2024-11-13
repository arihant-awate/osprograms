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
