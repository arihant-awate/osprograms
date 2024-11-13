#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

using namespace std;

void calculateEvenSum(const vector<int>& arr) {
    int sum = 0;
    for (int num : arr) {
        if (num % 2 == 0) {
            sum += num;
        }
    }
    cout << "Sum of even numbers in the array (Parent Process): " << sum << endl;
}

void calculateOddSum(const vector<int>& arr) {
    int sum = 0;
    for (int num : arr) {
        if (num % 2 != 0) {
            sum += num;
        }
    }
    cout << "Sum of odd numbers in the array (Child Process): " << sum << endl;
}

int main() {
    // Sample array
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Creating a child process using fork()
    pid_t pid = fork();

    if (pid == -1) {
        // Fork failed
        cerr << "Fork failed!" << endl;
        return 1;
    } else if (pid == 0) {
        // This is the child process
        calculateOddSum(arr);

        // Simulate a Zombie Process by terminating without parent calling wait()
        // The child process terminates, and the parent process has not yet called wait
        cout << "Child process is terminating, becoming a Zombie process!" << endl;
        _exit(0);
    } else {
        // This is the parent process
        calculateEvenSum(arr);

        // Simulate Orphan Process by terminating before the child process
        // Parent process terminates before the child has a chance to terminate
        cout << "Parent process is terminating, leaving the child process as orphan!" << endl;
        sleep(2); // Sleep to allow child process to execute and become orphaned

        // Wait for child process to avoid Zombie process
        wait(nullptr);

        cout << "Parent process has terminated." << endl;
    }

    return 0;
}

/*
    Program Description:
    This C++ program demonstrates:
    1. **Zombie Process**: A child process terminates, but the parent has not yet called `wait()` to collect the exit status, resulting in a zombie process.
    2. **Orphan Process**: The child process becomes an orphan after the parent terminates first, and `init` becomes the parent.
    3. **Sum of Even and Odd Numbers**: The program calculates the sum of even numbers in the array in the parent process, and the sum of odd numbers in the child process.

    FAQ Section:

    Q1: **What is a Zombie Process?**
    A1: A **Zombie Process** is a process that has completed execution but still has an entry in the process table. This occurs when the parent process has not called `wait()` to read the exit status of the child process.

    Q2: **What is an Orphan Process?**
    A2: An **Orphan Process** is a child process whose parent has terminated. In this case, the `init` process (process ID 1) becomes the new parent.

    Q3: **What happens when the parent terminates before the child?**
    A3: If the parent process terminates before the child process, the child becomes an orphan and is adopted by the `init` process.

    Q4: **How is the sum of even and odd numbers calculated in the program?**
    A4: The **parent process** calculates the sum of even numbers in the array, while the **child process** calculates the sum of odd numbers in the array. Each process is responsible for one part of the task, which is executed concurrently.

    Q5: **How do we simulate a Zombie process in the program?**
    A5: The child process terminates (`_exit(0)`) before the parent has a chance to call `wait()`, simulating a zombie process.

    Q6: **How does the parent process cause the child to become orphaned?**
    A6: The parent process terminates before the child has a chance to terminate, making the child an orphan. The operating system then assigns the `init` process as the parent of the orphaned child.
*/
