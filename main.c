/*
 * Course: CS2040
 * Pile of Instructions - Entry point function
 * Name: Alex Ruchti
 * Created: 05/06/2020
 */
 
#include "machine.h"
#include <stdlib.h>  // Needed for malloc and free
#include <stdint.h>  // Needed for uint8_t and int8_t
#include <stdio.h>   // Needed for input and output functions

// Structure declaration for an instruction
//   Two bytes - the first byte is an unsigned op code
//               the second byte is a signed value
struct instruction_t {
    uint8_t op_code;
    int8_t value;
};

int main(int argc, char **argv) {
    
    // Step 1: Get the path to the file to open
    // argv[0] is always the name of the program
    // argv[1] is the first command line argument
    if(argc < 2) {
        printf("ERROR: Program file is required\n");
        return 1;
    }
    
    // Step 2: Open the file with fopen
    // fopen returns a FILE pointer, the pointer is NULL if the file can't be opened
    FILE* myfile = fopen(argv[1], "r");
    if(myfile == NULL) {
        printf("ERROR: Unable to open: %s\n", argv[1]);
        return 1;
    }
    
    // Step 3: Read instructions from the file with fread
    //
    // fread reads items from a file:
    //    The first parameter is a pointer to a location in memory to store
    //        the read data
    //    The second parameter is how big an item is
    //    The third parameter is how many items to read
    //    The fourth parameter is a FILE pointer to read from
    //
    //  Here we want to read 1 instruction at a time.  The size of the
    //    instruction is sizeof(struct instruction_t)
    //
    // fread returns 0 when the end of file is reached or if there was an error
    struct instruction_t next_instruction;
    int exitcode = 1;
    machine* mac = (machine*)malloc(sizeof(machine));
    stack* st = create_stack();
    mac->st = st;

    while(fread(&next_instruction, sizeof(struct instruction_t), 1, myfile) && exitcode != -1) {
        exitcode = run_command(mac, next_instruction.op_code, next_instruction.value);
    }
    // Check if there was an error reading the file with ferror
    if(ferror(myfile)) {
        printf("ERROR: Unable to read from %s\n", argv[1]);
        delete_stack(mac->st);
        free(mac);
        // Need to close the file even though there was an error
        fclose(myfile);
        return 1;
    }
    
    delete_stack(mac->st);
    free(mac);
    // Step 4: Made it to the end of the file
    // Close the file and return
    fclose(myfile);
    return 0;
}