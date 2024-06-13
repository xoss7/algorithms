#include <stdio.h>
#include <stdlib.h>


typedef struct stack {
    int item;
    struct stack* next;
} stack;


void push(int item, stack** top) {
    stack* node = (stack*)malloc(sizeof(stack));
    node->item = item;
    node->next = *top;
    *top = node;
}


stack* pop(stack** top) {
    if (*top == NULL) { return NULL; } /* Do nothing if stack's empty */
    stack* node = *top;
    *top = (*top)->next;
    return node;
}

void printStack(stack* top) {
    while (top != NULL) {
        printf("%d -> ", top->item);
        top = top->next;
    }
    printf("NULL\n");
}