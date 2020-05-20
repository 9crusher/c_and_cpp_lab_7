/*
 * Course: CS2040
 * Pile of Instructions - Header for pilemachine stack methods
 * Name: Alex Ruchti
 * Created: 05/20/2020
 */
 
#ifndef STACK_H
#define STACK_H

#include <stdint.h> // int8_t use

/*
 * Node struct for a node in the
 * stack linked list
 */
typedef struct node {
    int8_t value;
    struct node* prev;
    struct node* next;
} node;

/*
 * Stack struct representing the stack
 * of the pilemachine
 */
typedef struct {
    node* top;
} stack;


/*
 * Pushes a value onto the stack
 */
void stack_push(stack* st, int8_t value);

/*
 * Pops a value off the top of the stack
 * and returns it. Sets the exit code int
 * to -1 if there is an error
 * e.g. stack is empty
 */
int8_t stack_pop(stack* st, int* exit_code);

/*
 * Peeks the item on top of the stack. Sets
 * exit code int to -1 if there is an error
 * e.g. stack is empty
 */
int8_t stack_peek(stack* st, int* exit_code);

/*
 * Cleans up stack memory
 */
void free_vals(stack* st);
#endif
