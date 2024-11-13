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
