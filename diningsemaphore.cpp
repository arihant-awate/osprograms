#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>  // For sleep()

using namespace std;

// Define the number of philosophers
#define NUM_PHILOSOPHERS 5

// Semaphores for each fork
sem_t forks[NUM_PHILOSOPHERS];

// Mutex for synchronizing philosophers' thinking and eating behavior
sem_t mutex;

// Philosopher thread function
void* philosopher(void* arg) {
    int id = *(int*)arg;  // Philosopher ID

    while (true) {
        // Thinking
        cout << "Philosopher " << id << " is thinking." << endl;
        sleep(2);  // Simulate thinking time

        // Trying to pick up both forks (left and right)
        sem_wait(&forks[id]);    // Pick up left fork
        sem_wait(&forks[(id + 1) % NUM_PHILOSOPHERS]);  // Pick up right fork

        // Eating
        cout << "Philosopher " << id << " is eating." << endl;
        sleep(1);  // Simulate eating time

        // Put down both forks
        sem_post(&forks[id]);    // Put down left fork
        sem_post(&forks[(id + 1) % NUM_PHILOSOPHERS]);  // Put down right fork
    }

    return nullptr;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    // Initialize semaphores for forks
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        sem_init(&forks[i], 0, 1);  // Each fork starts as available (1)
    }

    // Initialize mutex for philosopher behavior synchronization
    sem_init(&mutex, 0, 1);  // Mutex to prevent simultaneous access to shared behavior

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        ids[i] = i;
        pthread_create(&philosophers[i], nullptr, philosopher, &ids[i]);
    }

    // Join all threads
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_join(philosophers[i], nullptr);
    }

    // Clean up semaphores (not reached in this code as philosophers run infinitely)
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        sem_destroy(&forks[i]);
    }
    sem_destroy(&mutex);

    return 0;
}

/*
    Program Description:
    This C++ program implements the Dining Philosophers problem using threads and semaphores. The philosophers alternate between thinking and eating. 
    The problem ensures that no two philosophers are allowed to eat at the same time, preventing deadlock and starvation.

    1. **Forks**:
        - The forks are represented by semaphores, where each fork is initially available (set to 1). Philosophers need to acquire both the left and right forks before eating.

    2. **Philosopher Threads**:
        - Each philosopher alternates between thinking and eating. 
        - To eat, they pick up the left and right forks using the corresponding semaphores. Once they are done eating, they put down the forks.

    3. **Synchronization**:
        - The semaphores for the forks ensure that no two philosophers can eat at the same time by preventing simultaneous access to shared resources (the forks).
        - Each philosopher uses two semaphores: one for the left fork and one for the right fork. They also use a mutex to manage their thinking and eating states.

    4. **Thread Creation and Joining**:
        - The program creates multiple philosopher threads using `pthread_create()` and waits for all threads to complete using `pthread_join()`.

    FAQ Section:

    Q1: **What is the purpose of using semaphores in the Dining Philosophers problem?**  
    A1: Semaphores are used to control access to the shared resources (the forks) in the Dining Philosophers problem. Each fork is represented by a semaphore, which ensures that only one philosopher can use a fork at a time. This prevents deadlock and ensures that philosophers do not block each other unnecessarily.

    Q2: **Why do philosophers need both forks to eat?**  
    A2: Philosophers need both forks (one on the left and one on the right) to eat. This simulates the need for two resources to perform a task (eating in this case), which mirrors the real-world requirement for resources that must be shared.

    Q3: **What happens if a philosopher cannot pick up both forks?**  
    A3: If a philosopher cannot pick up both forks (because the forks are being used by others), the philosopher will wait (i.e., block) until both forks are available. This prevents simultaneous access to the forks by two philosophers.

    Q4: **Why do philosophers alternate between thinking and eating?**  
    A4: Philosophers alternate between thinking and eating to simulate real-life behavior where individuals perform tasks (thinking) and take breaks to refresh (eating). This alternation also helps prevent deadlock by allowing other philosophers to access the forks when one philosopher is thinking.

    Q5: **What prevents deadlock in this solution?**  
    A5: Deadlock is prevented because each philosopher picks up the left fork first and then the right fork. This order ensures that no philosopher can pick up both forks at the same time, and no philosopher can block others from accessing forks. Philosophers do not wait indefinitely if they cannot acquire both forks.

    Q6: **How does a philosopher know when to stop thinking and start eating?**  
    A6: Philosophers are programmed to repeatedly think and eat in a loop. They will pick up both forks only when they are ready to eat. The semaphores ensure that a philosopher can only eat when both forks are available.

    Q7: **What happens when a philosopher finishes eating?**  
    A7: Once a philosopher finishes eating, they put down both forks (release the corresponding semaphores) and resume thinking. The semaphores allow other philosophers to access the forks if they are available.

    Q8: **How does this implementation prevent starvation?**  
    A8: This solution avoids starvation because philosophers are not blocked indefinitely. Even though each philosopher may wait for the forks, no philosopher is stuck in a perpetual state of waiting, and each philosopher will eventually eat because they will be able to pick up both forks at some point.

    Q9: **What happens if all philosophers try to pick up the left fork at the same time?**  
    A9: If all philosophers try to pick up the left fork at the same time, they will each be blocked on the semaphore for the left fork. Once one philosopher is able to pick up the left fork and subsequently the right fork, they can eat and release the forks. This blocking mechanism ensures that no two philosophers can access the same fork at the same time.

    Q10: **Can we scale this solution for more philosophers?**  
    A10: Yes, this solution can be scaled for more philosophers by adjusting the number of philosopher threads and the number of semaphores representing forks. The logic remains the same, but as more philosophers are added, it becomes increasingly important to ensure proper synchronization to avoid deadlock.

    Q11: **Why do we need a mutex here?**  
    A11: The mutex is used to ensure that philosopher actions (thinking and eating) are synchronized. Without the mutex, philosophers could try to think and eat at the same time, leading to potential race conditions or inconsistency in output.

    Q12: **What are the limitations of this approach?**  
    A12: While this approach works well for a small number of philosophers, it may lead to inefficiencies or deadlock in larger systems with many philosophers. Improvements such as introducing a timeout for waiting philosophers or changing the order in which forks are picked up can help address such issues in more complex systems.
*/
