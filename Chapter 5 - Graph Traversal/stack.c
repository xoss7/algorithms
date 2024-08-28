#include <stdlib.h>

#include "stack.h"

bool empty(stack *s) {
    return (s == NULL);
}

void init_stack(stack** s) {
    *s = (stack*)malloc(sizeof(stack));
    *s = NULL;
}

void push(stack** s, int data) {
    stack* new = (stack*)malloc(sizeof(stack));
    new->data = data;
    new->next = *s;
    *s = new;
}

int pop(stack **s) {
    if ( empty(*s) )
        return -1;
    stack* top = *s;
    *s = (*s)->next;

    int data = top->data;
    free(top);
    return data;
}
