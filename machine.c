/*
 * Course: CS2040
 * Pile of Instructions - Pilemachine functions
 * Name: Alex Ruchti
 * Created: 05/20/2020
 */

#include "stack.h"
#include "machine.h"
#include <stdint.h> // int8_t use
#include <stdlib.h> // free and malloc
#include <stdio.h>  //printf

/*
 * Creates a stack in memory and returns
 * a pointer to it
 */
stack* create_stack(){
     stack* st = (stack*)malloc(sizeof(stack));
     st->top = NULL;
     return st;
}

/*
 * Removes the stack from memory
 */
void delete_stack(stack* st){
    free_vals(st);
    free(st);
}

/*
 * Runs a pilemachine command.
 * Returns -1 on error
 */
int run_command(machine* mac, int8_t opcode, int8_t value){
    switch(opcode){
        case 1:
            push(mac, value);
            return 0;
        case 2:
            return pop(mac);
        case 3:
            return swap(mac);
        case 4:
            return input(mac);
        case 5:
            return print_num(mac);
        case 6:
            return print_char(mac, value);
        case 7:
            return add(mac);
        case 8:
            return sub(mac);
        case 9:
            return mul(mac);
    }
    printf("ERROR: Invalid op code");
    return -1;
}

/*
 * Runs the push pilemachine command
 */
void push(machine* mac, int8_t value){
    stack_push(mac->st, value);
}

/*
 * Runs the pop pilemachine command.
 * returns -1 on error else 0
 */
int pop(machine* mac){
    int exitcode = 0;
    stack_pop(mac->st, &exitcode);
    if(exitcode == -1){
        printf("ERROR: empty stack, cannot pop value\n");
    }
    return exitcode;
}

/*
 * Runs the swap pilemachine command.
 * returns -1 on error else 0
 */
int swap(machine* mac){
    int exitcode = 0;
    int8_t value_one = stack_pop(mac->st, &exitcode); 
    int8_t value_two = stack_pop(mac->st, &exitcode);
    if(exitcode != -1){
        stack_push(mac->st, value_one);
        stack_push(mac->st, value_two);
    } else {
        printf("ERROR: stack must have two values to swap\n");
    }
    return exitcode;
}

/*
 * Runs the input pilemachine command.
 * returns -1 on error else 0
 */
int input(machine* mac){
    int input = 0;
    int exitcode = 0;
    printf("Please enter desired byte value\n");
    int num_scanned_items = scanf("%d", &input);
    if(num_scanned_items != 1){
        printf("Input value must be a number");
        return -1;
    }
    if(input > 127){
        printf("Input too large, must be less than or equal to 127\n");
        return -1;
    } else if(input < -128){
        printf("Input too small, must be greater than or equal to -128\n");
        return -1;
    }
    int8_t cast_input = (int8_t)input;
    if(exitcode == -1){
        printf("Number too large; input must be a byte\n");
        return -1;
    }
    stack_push(mac->st, cast_input);
    return 0;
}

/*
 * Runs the print num pilemachine command.
 * returns -1 on error else 0
 */
int print_num(machine* mac){
    int exitcode = 0;
    int8_t stack_byte = stack_peek(mac->st, &exitcode);
    if(exitcode == -1){
        printf("Cannot print: Nothing on stack\n");
        return -1;
    }
    printf("%d \n", (int)stack_byte);
    return 0;
}

/*
 * Runs the print char pilemachine command.
 * returns -1 on error else 0
 */
int print_char(machine* mac, int8_t value){
    char byte_char = (char)value;
    printf("%c \n", byte_char);
    return 0;
}

/*
 * Runs the add pilemachine command.
 * returns -1 on error else 0
 */
int add(machine* mac){
    int exitcode = 0;
    int8_t value_one = stack_pop(mac->st, &exitcode);
    int8_t value_two = stack_pop(mac->st, &exitcode);
    if(exitcode == -1){
        printf("Error: Cannot add fewer than two values on stack\n");
        return -1;
    }
    int op_result = value_one + value_two;
    if(op_result > 127){
        printf("Overflow: operation resulted in overflow\n");
        return -1;
    }
    if(op_result < -128){
        printf("Underflow: operation resulted in underflow\n");
        return -1;
    } 
    int8_t cast_result = (int8_t)op_result;
    stack_push(mac->st, cast_result);
    return 0;
}

/*
 * Runs the sub pilemachine command.
 * returns -1 on error else 0
 */
int sub(machine* mac){
    int exitcode = 0;
    int8_t value_one = stack_pop(mac->st, &exitcode);
    int8_t value_two = stack_pop(mac->st, &exitcode);
    if(exitcode == -1){
        printf("Error: Cannot subtract fewer than two values on stack\n");
        return -1;
    }
    int op_result = value_one - value_two;
    if(op_result > 127){
        printf("Overflow: operation resulted in overflow\n");
        return -1;
    }
    if(op_result < -128){
        printf("Underflow: operation resulted in underflow\n");
        return -1;
    } 
    int8_t cast_result = (int8_t)op_result;
    stack_push(mac->st, cast_result);
    return 0;
}

/*
 * Runs the mul pilemachine command.
 * returns -1 on error else 0
 */
int mul(machine* mac){
    int exitcode = 0;
    int8_t value_one = stack_pop(mac->st, &exitcode);
    int8_t value_two = stack_pop(mac->st, &exitcode);
    if(exitcode == -1){
        printf("Error: Cannot multiply fewer than two values on stack\n");
        return -1;
    }
    int op_result = value_one * value_two;
    if(op_result > 127){
        printf("Overflow: operation resulted in overflow\n");
        return -1;
    }
    if(op_result < -128){
        printf("Underflow: operation resulted in underflow\n");
        return -1;
    } 
    int8_t cast_result = (int8_t)op_result;
    stack_push(mac->st, cast_result);
    return 0;
}


