#include "stack.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h> // used for malloc

void stack_push(stack* st, int8_t value){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->value = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    if(st->top == NULL){
        st->top = newNode;
        st->bottom = newNode;
    } else {
        newNode->prev = st->top;
        st->top->next = newNode;
        st->top = newNode;
    }
}

int8_t stack_pop(stack* st, int* exit_code){
    if(st->top == NULL){
        (*exit_code) = -1;
        return -1;
    }
    int8_t value = st->top->value;
    // set top to prev and free previous top
    st->top = st->top->prev;
    if(st->top != NULL){
        free(st->top->next);
        st->top->next = NULL;
    } else {
        free(st->bottom);
        st->bottom = NULL;
    }
    (*exit_code) = 0;
    return value;
}

int8_t stack_peek(stack* st, int* exit_code){
    if(st->top == NULL){
        (*exit_code) = -1;
        return -1;
    }
    (*exit_code) = 0;
    return st->top->value;
}

void free_vals(stack* st){
    node* current = st->bottom;
    node* next = NULL;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
}