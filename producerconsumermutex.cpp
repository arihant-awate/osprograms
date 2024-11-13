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
