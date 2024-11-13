#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class JobProcessor {
private:
    vector<string> validOpcodes = {"MOV", "ADD", "SUB", "JMP", "NOP"}; // List of valid opcodes

public:
    // Function to check for invalid opcodes and simulate raising an interrupt
    void checkForOpcodeError(const vector<string>& job) {
        for (const string& instruction : job) {
            // Get the opcode (the first word in the instruction)
            stringstream ss(instruction);
            string opcode;
            ss >> opcode;

            // Check if the opcode is valid
            if (find(validOpcodes.begin(), validOpcodes.end(), opcode) == validOpcodes.end()) {
                // If the opcode is invalid, raise an interrupt (handle error)
                raiseInterrupt(opcode);
                return; // Exit after raising the interrupt
            }
        }

        cout << "All instructions are valid. No errors detected." << endl;
    }

    // Function to simulate raising an interrupt when an invalid opcode is found
    void raiseInterrupt(const string& invalidOpcode) {
        cout << "ERROR: Invalid opcode encountered: " << invalidOpcode << endl;
        cout << "Raising interrupt to handle the error." << endl;
        // Simulating interrupt handling (could be a termination or logging)
        exit(1);  // Simulate terminating the program with an error
    }
};

int main() {
    // Example job with opcodes
    vector<string> job = {
        "MOV A, 5",
        "ADD A, B",
        "INVALID_OP X, Y",  // This is an invalid opcode for simulation
        "JMP 100"
    };

    JobProcessor processor;

    // Check the job for opcode errors
    processor.checkForOpcodeError(job);

    return 0;
}

/*
    Program Description:
    This C++ program simulates the detection of an **Opcode Error** in a given job. The program checks each instruction 
    to ensure it contains a valid opcode. If an invalid opcode is found, it raises an interrupt (simulated by printing 
    an error message and terminating the program).

    FAQ Section:

    Q1: **What is an Opcode Error?**
    A1: An **Opcode Error** occurs when the processor encounters an invalid or unrecognized instruction (opcode) during 
       the execution of a job.

    Q2: **How does the program check for opcode errors?**
    A2: The program reads each instruction in the job, extracts the opcode, and checks if it belongs to a predefined list 
       of valid opcodes. If the opcode is not valid, an interrupt is raised.

    Q3: **What happens when an invalid opcode is detected?**
    A3: If an invalid opcode is encountered, the program raises an interrupt, prints an error message, and terminates the program.

    Q4: **What are the valid opcodes in this program?**
    A4: The valid opcodes in this program are: `MOV`, `ADD`, `SUB`, `JMP`, and `NOP`. Any other opcode is considered invalid.

    Q5: **How does the interrupt mechanism work in the simulation?**
    A5: The interrupt mechanism is simulated by printing an error message and terminating the program using the `exit(1)` function.
*/
