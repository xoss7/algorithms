#include "graph.h"

typedef struct node {
    int vID;
    struct node* next;
} node;


typedef struct queue {
    node* front;
    node* tail;
} queue;


void init_queue(queue**);
bool empty(queue*);
void enqueue(queue*, int);
int dequeue(queue*);
void print_queue(queue*);
