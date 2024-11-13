#include <iostream>
#include <unistd.h>        // For system calls like fork(), getpid(), getppid(), alarm(), etc.
#include <sys/types.h>     // For pid_t and other data types
#include <sys/wait.h>      // For wait()
#include <ctime>           // For time-related functions like gettimeofday()
#include <cstring>         // For strerror() and error handling
#include <errno.h>         // For error number definitions
#include <signal.h>        // For alarm() and signal handling

using namespace std;

int main() {
    pid_t pid;

    // Demonstrating getpid() system call to get the process ID
    pid_t process_id = getpid();
    cout << "Process ID: " << process_id << endl;

    // Demonstrating getppid() system call to get the parent process ID
    pid_t parent_process_id = getppid();
    cout << "Parent Process ID: " << parent_process_id << endl;

    // Demonstrating gettimeofday() to get the current time
    //struct timeval tv;
  // gettimeofday(&tv, NULL);
   // cout << "Current time: " << tv.tv_sec << " seconds and " << tv.tv_usec << " microseconds since the Epoch" << endl;

    // Creating a child process with fork()
    pid = fork(); 
    if (pid < 0) {
        cerr << "Fork failed: " << strerror(errno) << endl;
        return 1; // Exit with error
    }
    else if (pid == 0) {
        // Child process block

        // Using getpid() again in the child process
        cout << "Child Process ID (from child): " << getpid() << endl;
        
        // Using getppid() in the child process (getting the parent process ID)
        cout << "Parent Process ID (from child): " << getppid() << endl;

        // Using alarm() system call to set a timer for 5 seconds
        cout << "Child process sets an alarm to go off in 5 seconds." << endl;
        alarm(5); // Set an alarm for 5 seconds
        
        // Simulate some activity before alarm goes off
        cout << "Child process is doing some work..." << endl;

        // Wait for the alarm to signal (handled by signal handling mechanism, but just an illustration)
        // Here, the program will continue and terminate without waiting explicitly for the alarm

        // Using exit() to terminate the child process
        exit(0); // This will terminate the child process
    }
    else {
        // Parent process block

        // The parent process waits for the child to terminate
        int status;
        wait(&status); // Wait for child process to terminate

        // If the child process terminated normally
        if (WIFEXITED(status)) {
            cout << "Child process exited with status " << WEXITSTATUS(status) << endl;
        }
        else {
            cout << "Child process did not terminate normally." << endl;
        }

        // The parent can perform some additional work, if necessary
        cout << "Parent process completes execution." << endl;
    }

    return 0; // Successful execution
}

/*
    Program Description:
    This C++ program demonstrates the use of various system calls commonly used in UNIX-based systems. 
    It performs the following operations:
    
    1. **Process Creation and Management:**
        - Uses `fork()` to create a child process.
        - In the child process, it uses `getpid()` to get the child’s process ID, and `getppid()` to get the parent’s process ID.
        - The child process sets an alarm using `alarm()` to go off in 5 seconds and continues execution.
        - The parent process waits for the child process to terminate using `wait()`.
    
    2. **Time Operations:**
        - Uses `gettimeofday()` to display the current time (in seconds and microseconds).
    
    3. **Process Termination:**
        - The child process terminates using `exit(0)`.
    
    The program demonstrates basic system call usage like `getpid()`, `getppid()`, `alarm()`, `wait()`, and `gettimeofday()`. It also shows process creation with `fork()` and termination with `exit()`. The program is entirely hard-coded and does not require any user input. Detailed comments are provided for each line to explain the functionality.

    FAQ Section:

    Q1: What is the `getpid()` system call used for?
    A1: `getpid()` returns the process ID of the calling process. It is useful for identifying the current process in a multi-process environment.

    Q2: How is `getppid()` different from `getpid()`?
    A2: `getppid()` returns the process ID of the parent of the calling process, while `getpid()` returns the ID of the current process.

    Q3: What does the `fork()` system call do?
    A3: `fork()` creates a new process by duplicating the current process. It returns 0 in the child process and the child's process ID in the parent process.

    Q4: What is the purpose of the `wait()` system call?
    A4: `wait()` is used by the parent process to wait for the child process to terminate. It allows the parent to obtain the exit status of the child.

    Q5: What does `exit()` do?
    A5: `exit()` terminates the current process and optionally provides an exit status to the parent process. The status is used to indicate whether the process terminated successfully or with an error.

    Q6: How does `alarm()` work in the program?
    A6: The `alarm()` system call sets an alarm for a specified number of seconds. When the timer expires, a signal (SIGALRM) is sent to the process. This is a simple demonstration and doesn't handle the signal explicitly.

    Q7: What does `gettimeofday()` do?
    A7: `gettimeofday()` gets the current time with microsecond precision. It returns the time elapsed since the Unix Epoch (January 1, 1970) in seconds and microseconds.

    Q8: Why is `exit()` used in the child process?
    A8: `exit()` is used to terminate the child process gracefully. It sends an exit status to the parent process, allowing the parent to determine how the child terminated.
*/

