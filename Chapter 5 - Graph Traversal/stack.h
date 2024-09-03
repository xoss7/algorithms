#include "graph.h"

typedef enum state {
    UNDISCOVERED,
    DISCOVERED,
    PROCESSED
} state;

typedef struct stack {
    int data;
    struct stack* next;
} stack;


bool empty(stack*);
int pop(stack**);
void push(stack**, int);
void init_stack(stack**);
void print_stack(stack*);
