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
