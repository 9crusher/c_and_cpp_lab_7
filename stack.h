
#ifndef STACK_H
#define STACK_H
#include <stdint.h>
typedef struct node {
    int8_t value;
    struct node* prev;
    struct node* next;
} node;

typedef struct {
    node* top;
    node* bottom;
} stack;


void stack_push(stack* st, int8_t value);
int8_t stack_pop(stack* st, int* exit_code);
int8_t stack_peek(stack* st, int* exit_code);
void free_vals(stack* st);

#endif
