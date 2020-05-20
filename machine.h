/*
 * Course: CS2040
 * Pile of Instructions - Header for machine
 * Name: Alex Ruchti
 * Created: 05/20/2020
 */

#ifndef MACHINE_H
#define MACHINE_H

#include "stack.h"
#include <stdint.h> // int8_t use

/*
 * Struct representing a pilemachine
 * holds a pointer to the pilemachine stack
 */
typedef struct {
    stack* st;
} machine;

/*
 * Creates a stack in memory and returns
 * a pointer to it
 */
stack* create_stack();

/*
 * Removes the stack from memory
 */
void delete_stack(stack* st);

/*
 * Runs a pilemachine command
 */
int run_command(machine* mac, int8_t opcode, int8_t value);

/*
 * Runs the push pilemachine command
 */
void push(machine* mac, int8_t value);

/*
 * Runs the pop pilemachine command.
 * returns -1 on error else 0
 */
int pop(machine* mac);

/*
 * Runs the swap pilemachine command.
 * returns -1 on error else 0
 */
int swap(machine* mac);

/*
 * Runs the input pilemachine command.
 * returns -1 on error else 0
 */
int input(machine* mac);

/*
 * Runs the print num pilemachine command.
 * returns -1 on error else 0
 */
int print_num(machine* mac);

/*
 * Runs the print char pilemachine command.
 * returns -1 on error else 0
 */
int print_char(machine* mac, int8_t value);

/*
 * Runs the add pilemachine command.
 * returns -1 on error else 0
 */
int add(machine* mac);

/*
 * Runs the sub pilemachine command.
 * returns -1 on error else 0
 */
int sub(machine* mac);

/*
 * Runs the mul pilemachine command.
 * returns -1 on error else 0
 */
int mul(machine* mac);
#endif