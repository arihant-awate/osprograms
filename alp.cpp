#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class ALPLoader {
private:
    vector<string> memory;  // Main memory represented as a vector of strings
    int memorySize;         // The size of main memory

public:
    // Constructor to initialize memory size and memory
    ALPLoader(int size) : memorySize(size) {
        memory.resize(memorySize);  // Resize the memory to fit the given size
    }

    // Function to load ALP program from the input file into main memory
    bool loadALPProgram(const string& fileName) {
        ifstream file(fileName);
        if (!file.is_open()) {
            cerr << "Error opening the file!" << endl;
            return false;
        }

        string instruction;
        int i = 0;
        
        // Load instructions from the file into the memory
        while (getline(file, instruction) && i < memorySize) {
            memory[i] = instruction;  // Store each instruction in memory
            i++;
        }

        file.close();
        return true;
    }

    // Function to print the contents of the memory
    void printMemory() {
        cout << "\nMain Memory (loaded ALP instructions):\n";
        cout << "--------------------------------------------\n";
        for (int i = 0; i < memorySize; i++) {
            if (!memory[i].empty()) {
                cout << "Memory Location " << setw(3) << i << ": " << memory[i] << endl;
            } else {
                break;  // Stop when we reach an empty memory location
            }
        }
        cout << "--------------------------------------------\n";
    }
};

int main() {
    int memorySize = 10;  // Size of the main memory (number of locations)
    string fileName = "example.txt";  // Name of the input file containing the ALP program

    ALPLoader loader(memorySize);

    // Load the ALP program from the file into main memory
    if (loader.loadALPProgram(fileName)) {
        // Print the loaded memory
        loader.printMemory();
    } else {
        cerr << "Failed to load ALP program!" << endl;
    }

    return 0;
}

/*
    Program Description:
    This C++ program simulates the loading of an Assembly Language Program (ALP) from an input file into the main memory. 
    The ALP program is represented as a text file where each instruction is placed on a separate line. 
    The program loads each instruction from the file into an array (simulating memory) and prints the memory content.

    FAQ Section:

    Q1: **What is an ALP program in this context?**
    A1: An **ALP program** is a sequence of assembly language instructions that are read from an input file and stored in memory. Each line in the file represents a single instruction.

    Q2: **How does the program load the ALP into memory?**
    A2: The program reads each instruction from the file line by line and stores it in the corresponding memory location in the memory array (simulated as a vector in this case).

    Q3: **What happens if the input file is too large for memory?**
    A3: If the input file contains more instructions than the available memory, only the first `memorySize` instructions are loaded. Any extra instructions are ignored.

    Q4: **Can the program handle any ALP format?**
    A4: Yes, as long as the ALP format is simple (one instruction per line), the program can handle it. The instructions are stored as strings.

    Q5: **How does the program display the memory?**
    A5: After loading the ALP program into memory, the program prints the contents of the memory locations, showing each instruction stored in memory.
*/


// new section //
/*MOV A, 1
ADD B, A
SUB C, B
JMP 100 */


