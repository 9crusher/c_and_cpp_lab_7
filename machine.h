#ifndef MACHINE_H
#define MACHINE_H
#include "stack.h"
#include <stdint.h>

typedef struct {
    stack* st;
} machine;
stack* create_stack();
void delete_stack(stack* st);
int push(machine* mac, int8_t value);
int pop(machine* mac);
int swap(machine* mac);
int input(machine* mac);
int print_num(machine* mac);
int print_char(machine* mac, int8_t value);
int add(machine* mac);
int sub(machine* mac);
int mul(machine* mac);
#endif