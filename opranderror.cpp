#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm> // Include algorithm for find()

using namespace std;

class JobProcessor {
private:
    vector<string> validRegisters = {"A", "B", "C", "D"}; // List of valid registers

public:
    // Function to check for operand errors and simulate raising an interrupt
    void checkForOperandError(const vector<string>& job) {
        for (const string& instruction : job) {
            // Parse the instruction to get the operand(s)
            stringstream ss(instruction);
            string opcode, operand1, operand2;
            ss >> opcode >> operand1;

            // Check if the instruction has two operands (for instructions like ADD, MOV, etc.)
            if (ss >> operand2) {
                if (!isValidOperand(operand1) || !isValidOperand(operand2)) {
                    // If any operand is invalid, raise an interrupt
                    raiseInterrupt(instruction);
                    return; // Exit after raising the interrupt
                }
            } else {
                if (!isValidOperand(operand1)) {
                    // If the single operand is invalid, raise an interrupt
                    raiseInterrupt(instruction);
                    return; // Exit after raising the interrupt
                }
            }
        }

        cout << "All instructions are valid. No operand errors detected." << endl;
    }

    // Function to check if an operand is valid (either a register or a number)
    bool isValidOperand(const string& operand) {
        // Check if the operand is a valid register
        if (find(validRegisters.begin(), validRegisters.end(), operand) != validRegisters.end()) {
            return true;
        }

        // Check if the operand is a valid number (could be negative, integer)
        for (char c : operand) {
            if (!isdigit(c) && c != '-') {
                return false;
            }
        }

        return true;
    }

    // Function to simulate raising an interrupt when an invalid operand is found
    void raiseInterrupt(const string& invalidInstruction) {
        cout << "ERROR: Invalid operand in instruction: " << invalidInstruction << endl;
        cout << "Raising interrupt to handle the error." << endl;
        // Simulating interrupt handling (could be a termination or logging)
        exit(1);  // Simulate terminating the program with an error
    }
};

int main() {
    // Example job with opcodes and operands
    vector<string> job = {
        "MOV A, 5",        // Valid instruction
        "ADD A, B",        // Valid instruction
        "MOV X, 10",       // Invalid operand (X is not a valid register)
        "SUB A, -3",       // Valid instruction with negative number operand
        "JMP 100"          // Invalid instruction without operand
    };

    JobProcessor processor;

    // Check the job for operand errors
    processor.checkForOperandError(job);

    return 0;
}

/*
    Program Description:
    This C++ program simulates the detection of an **Operand Error** in a given job. The program checks each instruction 
    to ensure it contains valid operands. If an invalid operand is found (either an invalid register or an invalid number), 
    it raises an interrupt (simulated by printing an error message and terminating the program).

    FAQ Section:

    Q1: **What is an Operand Error?**
    A1: An **Operand Error** occurs when the operand used in an instruction is invalid. The operand could be an invalid register 
       or an invalid number that the processor cannot recognize.

    Q2: **How does the program check for operand errors?**
    A2: The program checks each instruction for valid operands by validating whether the operand is a recognized register or a 
       valid number.

    Q3: **What happens when an invalid operand is detected?**
    A3: If an invalid operand is encountered, the program raises an interrupt by printing an error message and terminating the program.

    Q4: **How does the program validate operands?**
    A4: The program checks if the operand is either a valid register (e.g., `A`, `B`, `C`, `D`) or a valid number (including 
       negative numbers). If the operand does not meet these conditions, it is considered invalid.

    Q5: **How does the interrupt mechanism work in the simulation?**
    A5: The interrupt mechanism is simulated by printing an error message and terminating the program using the `exit(1)` function.
*/
