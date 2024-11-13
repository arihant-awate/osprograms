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
