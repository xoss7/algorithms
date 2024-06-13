#include <stdio.h>
#include <stdlib.h>


typedef struct stack {
    int item;
    struct stack* next;
} stack;

stack* newStack(int data) {
    stack* node = (stack*)malloc(sizeof(stack));
    node->item = data;
    node->next = NULL;
    return node;
}

void push(int item, stack** top) {
    stack* node = newStack(item);
    node->next = *top;
    *top = node;
}


int pop(stack** top) {
    if (*top == NULL) { return EXIT_FAILURE; } /* Do nothing if stack's empty */
    stack* node = *top;
    *top = (*top)->next;
    int popped = node->item;
    free(node);
    return popped;
}

void printStack(stack* top) {
    while (top != NULL) {
        printf("%d -> ", top->item);
        top = top->next;
    }
    printf("NULL\n");
}