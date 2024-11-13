#include <iostream>
#include <pthread.h>    // For pthread functionality
#include <vector>       // For dynamic arrays (vectors)
#include <cstring>      // For strerror() and error handling
#include <errno.h>      // For error number definitions

using namespace std;

// Matrix dimensions (for simplicity, we assume square matrices)
#define N 4  // Size of the matrix (N x N)

// Matrix data
int matrix1[N][N] = {{1, 2, 3, 4},
                     {5, 6, 7, 8},
                     {9, 10, 11, 12},
                     {13, 14, 15, 16}};

int matrix2[N][N] = {{16, 15, 14, 13},
                     {12, 11, 10, 9},
                     {8, 7, 6, 5},
                     {4, 3, 2, 1}};

int result[N][N];  // Result matrix to store the multiplication result

// Structure to pass data to the threads
struct ThreadData {
    int row;  // Row number to process
};

// Function to multiply a row by the second matrix
void* multiplyRow(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    int row = data->row;

    for (int col = 0; col < N; col++) {
        result[row][col] = 0;
        for (int k = 0; k < N; k++) {
            result[row][col] += matrix1[row][k] * matrix2[k][col];
        }
    }
    
    pthread_exit(0); // Exit the thread after completing its task
}

int main() {
    pthread_t threads[N];  // Array of threads
    ThreadData data[N];    // Array of data for each thread

    // Create threads to perform matrix multiplication
    for (int i = 0; i < N; i++) {
        data[i].row = i;  // Assign each thread a row to compute
        if (pthread_create(&threads[i], NULL, multiplyRow, (void*)&data[i]) != 0) {
            cerr << "Failed to create thread: " << strerror(errno) << endl;
            return 1; // Exit with error if thread creation fails
        }
    }

    // Wait for all threads to complete their execution
    for (int i = 0; i < N; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            cerr << "Failed to join thread: " << strerror(errno) << endl;
            return 1; // Exit with error if thread join fails
        }
    }

    // Display the result matrix
    cout << "Resultant Matrix: " << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    return 0; // Successful execution
}

/*
    Program Description:
    This C++ program demonstrates the use of multithreading for matrix multiplication using Pthreads.
    The program multiplies two N x N matrices using N threads. Each thread is responsible for calculating 
    one row of the resultant matrix. It uses the Pthreads library to create and manage threads.

    1. **Matrix Initialization**: 
        - Two matrices, `matrix1` and `matrix2`, are initialized with predefined values.
        - A result matrix, `result`, is created to store the multiplication output.

    2. **Thread Creation**:
        - The program creates `N` threads, where each thread computes one row of the resulting matrix.
        - The `multiplyRow` function computes one row of the matrix by multiplying corresponding rows of `matrix1` and `matrix2`.

    3. **Thread Synchronization**:
        - The `pthread_join()` function is used to ensure that the main program waits for all threads to finish their execution before proceeding.

    4. **Output**:
        - Once all threads finish their task, the result matrix is displayed.

    FAQ Section:

    Q1: What is the purpose of using Pthreads in this program?
    A1: Pthreads are used to perform matrix multiplication in parallel by dividing the task of calculating the result matrix into multiple threads, each handling a different row of the result matrix. This improves performance, especially for large matrices.

    Q2: How does the `pthread_create()` function work?
    A2: The `pthread_create()` function is used to create a new thread. It takes the thread identifier, attributes (NULL for default), the function to execute, and the argument to pass to the function. In this case, the function `multiplyRow` is executed by each thread.

    Q3: What does the `pthread_join()` function do?
    A3: `pthread_join()` is used to wait for a thread to terminate. It ensures that the main thread (main program) will not proceed until all the worker threads have finished their execution.

    Q4: Why are we passing a struct to each thread?
    A4: The struct `ThreadData` is used to pass data to the threads. Each thread requires the row number to compute, so we pass a struct containing this data to the thread function.

    Q5: What happens if the `pthread_create()` or `pthread_join()` call fails?
    A5: If `pthread_create()` or `pthread_join()` fails, an error message is displayed using `strerror()` and `errno`, and the program exits with an error code.

    Q6: How does matrix multiplication work in this program?
    A6: Matrix multiplication involves multiplying the rows of the first matrix by the columns of the second matrix and summing the products. Each thread in this program computes one row of the result matrix by performing this operation.

    Q7: How can this approach be extended to larger matrices?
    A7: This approach can be scaled to larger matrices by adjusting the matrix size (N) and creating additional threads accordingly. The parallelism improves as more threads are used for larger matrices.

*/

