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
