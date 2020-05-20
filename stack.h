/*
 * Course: CS2040
 * Pile of Instructions - Header for pilemachine stack methods
 * Name: Alex Ruchti
 * Created: 05/20/2020
 */
 
#ifndef STACK_H
#define STACK_H

#include <stdint.h> // int8_t use

typedef struct node {
    int8_t value;
    struct node* prev;
    struct node* next;
} node;

typedef struct {
    node* top;
} stack;


void stack_push(stack* st, int8_t value);
int8_t stack_pop(stack* st, int* exit_code);
int8_t stack_peek(stack* st, int* exit_code);
void free_vals(stack* st);
#endif
