/*
 * Course: CS2040
 * Pile of Instructions - The Pile Machine Assembler
 * Created: 05/06/2020
 */

#include <iostream>
#include <fstream>
using namespace std;

const int MIN_VALUE = -128;
const int MAX_VALUE = 127;

enum OP_CODE {
    PUSH = 1,
    POP = 2,
    SWAP = 3,
    INPUT = 4,
    PRINT_NUM = 5,
    PRINT_CHAR = 6,
    ADD = 7,
    SUB = 8,
    MUL = 9,
};

enum AssemblerOp {
    CHECK_FILE,
    WRITE_OUTPUT,
};

/**
 * @brief Check for a valid stack value
 * @param value - the value to check
 * @return true if value is valid, false if not
 */
bool validValue(const string& instructionName, int value) {
    if(value < MIN_VALUE) {
        cout << "ERROR: Invalid value for " << instructionName << 
            ". Value: " << value << " is less than minimum" << endl;
        return false;
    }
    if(value > MAX_VALUE) {
        cout << "ERROR: Invalid value for " << instructionName << 
            ". Value: " << value << " is greater than maximum" << endl;
        return false;
    }
    return true;
}

/**
 * @brief Perform a pass of the input file, performing the specified operation
 * @param inPath - The path to the input assembly file
 * @param outPath - The path to the output binary file
 * @param assemblerOp - The operation to perform
 * @return true on success, false otherwise
 */
bool processFile(const string& inPath, const string& outPath, AssemblerOp assemblerOp) {
    
    // Open the input file
    ifstream infile(inPath);
    if(infile.bad() || !infile.is_open()) {
        cout << "ERROR: Unable to open: " << inPath << endl;
        return false;
    }
    
    // if the operation is to write the output, then open the output file
    ofstream* outfile = nullptr;
    if(assemblerOp == WRITE_OUTPUT) {
        outfile = new ofstream(outPath);
        if(outfile->bad() || !(outfile->is_open())) {
            cout << "ERROR: Unable to open: " << outPath << endl;
            infile.close();
            return false;
        }
    }
    
    bool fileGood = true;
    char opBuffer[2];
    
    // Translate each instruction
    //    NOTE: instructions and values are case sensitive
    string input;
    infile >> input;
	while(infile) {
		if(input == "PUSH") {
			int value;
			infile >> value;
            if(!validValue("PUSH", value)) {
                fileGood = false;
                break;
            }
			opBuffer[0] = PUSH;
			opBuffer[1] = value;
		} else if(input == "POP" ) {
			opBuffer[0] = POP;
			opBuffer[1] = 0;
		} else if(input == "SWAP") {
			opBuffer[0] = SWAP;
			opBuffer[1] = 0;
		} else if(input == "INPUT") {
			opBuffer[0] = INPUT;
			opBuffer[1] = 0;
		} else if(input == "PRINT_NUM") {
			opBuffer[0] = PRINT_NUM;
			opBuffer[1] = 0;
		} else if(input == "PRINT_CHAR") {
			infile >> input;
			opBuffer[0] = PRINT_CHAR;
            if(input == "NL") {
                opBuffer[1] = '\n';
            } else if(input == "SP") {
                opBuffer[1] = ' ';
            } else {
                if(input.length() > 1) {
                    cout << "ERROR: Invalid character for PRINT_CHAR: " << input << endl;
                    fileGood = false;
                    break;
                }
                opBuffer[1] = input[0];
            }
		} else if(input == "ADD") {
			opBuffer[0] = ADD;
			opBuffer[1] = 0;
		} else if(input == "SUB") {
			opBuffer[0] = SUB;
			opBuffer[1] = 0;
		} else if(input == "MUL") {
			opBuffer[0] = MUL;
			opBuffer[1] = 0;
		} else {
            cout << "ERROR: Invalid operation: " << input << endl;
            fileGood = false;
            break;
        }
        
        // Write the binary output
        if(assemblerOp == WRITE_OUTPUT) {
            outfile->write(opBuffer, 2);
        }
		infile >> input;
	}
    
    // Close input and output files
    if(assemblerOp == WRITE_OUTPUT) {
        outfile->close();
        delete outfile;
    }
    infile.close();
    
    return fileGood;
}

int main(int argc, char** argv) {
    
    // Check for input files
    if(argc < 2) {
        cout << "ERROR: No input files" << endl;
        return 1;
    }

    string inputExt = ".asm";
    string outputExt = ".pgm";

    // Assemble each input file
    for(int i = 1; i < argc; i++) {
        
        // Verify input file and extension
        string inputPath = argv[i];
        if(inputPath.length() < inputExt.length() ||
            !std::equal(inputExt.rbegin(), inputExt.rend(), inputPath.rbegin())) {
            cout << "ERROR: Wrong input file type: " << inputPath << endl;
            continue;                    
        }
        
        // Set the output file and extension
        string outputPath = inputPath;
        outputPath.replace(outputPath.rfind('.', outputPath.length() + 1), outputExt.length(), outputExt);
        
        // Check the file for errors
        if(processFile(inputPath, outputPath, CHECK_FILE) == false) {
            continue;
        }
        
        // Write the binary program
        if(processFile(inputPath, outputPath, WRITE_OUTPUT) == false) {
            continue;
        }
    }
    
    return 0;
}
