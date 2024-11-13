#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <cstring>
using namespace std;

// Function to demonstrate process-related system calls
void process_related() {
    cout << "\n--- Process Related System Calls ---" << endl;

    // fork() system call - creates a new process
    pid_t pid = fork();

    if (pid == 0) { // Child process
        cout << "Child process created. PID = " << getpid() << endl;
    } else { // Parent process
        wait(NULL); // Parent waits for the child to finish
        cout << "Parent process. PID = " << getpid() << endl;
    }
}

// Function to demonstrate file-related system calls
void file_related() {
    cout << "\n--- File Related System Calls ---" << endl;

    // open() system call - opens/creates a file for writing
    int fd = open("example.txt", O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return;
    }
    write(fd, "Hello, World!\n", 14); // write() system call
    close(fd); // close() system call
    cout << "File written and closed successfully." << endl;

    // open() system call for reading
    fd = open("example.txt", O_RDONLY);
    char buffer[100];
    read(fd, buffer, 100); // read() system call
    cout << "Read from file: " << buffer;
    close(fd); // close() system call
}

// Function to demonstrate communication-related system calls
void communication_related() {
    cout << "\n--- Communication Related System Calls (pipe) ---" << endl;

    int fd[2];
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return;
    }

    pid_t pid = fork();
    if (pid == 0) { // Child process
        close(fd[0]); // Close unused read end
        write(fd[1], "Hello from child", 16);
        close(fd[1]); // Close write end after writing
    } else { // Parent process
        char buffer[20];
        close(fd[1]); // Close unused write end
        read(fd[0], buffer, sizeof(buffer));
        cout << "Parent received message: " << buffer << endl;
        close(fd[0]); // Close read end after reading
        wait(NULL); // Wait for the child process to finish
    }
}

int main() {
    process_related();
    file_related();
    communication_related();
    return 0;
}

/* 
FAQs:

1. Why do we use `fork()` and what does it do?
   - `fork()` is used to create a new process. After the `fork()`, we have two processes: the original (parent) and the newly created (child). Each process has its own unique PID.

2. What does the `wait()` system call do in this program?
   - `wait()` is used by the parent process to pause its execution until the child process has finished executing, ensuring synchronization between parent and child processes.

3. How is a file created and written to using system calls?
   - We use `open()` to create or open a file. `write()` is used to write data to the file, and `close()` is used to close the file after operations are complete.

4. What is a `pipe` and how is it used for communication in this program?
   - A `pipe` is a method of inter-process communication that allows data to flow from one process to another. Here, the child writes to the pipe, and the parent reads from it.

5. Why are `close()` calls important after `open()` and `pipe()`?
   - Closing file descriptors after use is important for resource management and prevents memory leaks or unintentional access to file data.

*/
