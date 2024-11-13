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
