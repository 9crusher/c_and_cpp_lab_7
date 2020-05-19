#include "stack.h"
#include "machine.h"
#include <stdint.h>
#include <stdlib.h>


stack* create_stack(){
     stack* st = (stack*)malloc(sizeof(stack));
     st->bottom = NULL;
     st->top = NULL;
     return st;
}

void delete_stack(stack* st){
    free_vals(st);
    free(st);
}

