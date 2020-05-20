/*
 * Course: CS2040
 * Pile of Instructions - Stack functions for pilemachine
 * Name: Alex Ruchti
 * Created: 05/20/2020
 */

#include "stack.h"
#include <stdint.h> // int8_t use
#include <stdlib.h> // used for malloc

void stack_push(stack* st, int8_t value){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->value = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    if(st->top == NULL){
        st->top = newNode;
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
    node* old_top = st->top;
    st->top = st->top->prev;
    free(old_top);
    if(st->top != NULL){
        st->top->next = NULL;
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
    node* current = st->top;
    node* prev = NULL;
    while(current != NULL){
        prev = current->prev;
        free(current);
        current = prev;
    }
}