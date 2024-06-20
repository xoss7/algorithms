#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    int item;
    struct node* next;
} node;

typedef struct queue
{
    node* head;
    node* tail;
} queue;


void enqueue(int item, queue* _queue) {
    node* newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL) { return; }
    newNode->item = item;
    newNode->next = NULL;

    if (_queue->head == NULL || _queue->tail == NULL) { /* file vide */
        _queue->head = _queue->tail = newNode;
    }
    else {
        _queue->tail->next = newNode;
        _queue->tail = newNode;
    }
}


int dequeue(queue* _queue) {
    if (_queue == NULL || _queue->head == NULL) { return NULL; } /* la file est vide */
    node* head = _queue->head;
    int headItem = head->item;

    _queue->head = _queue->head->next;

    free(head);
    return headItem;
}

node* searchQueue(int item, queue* _queue) {
    node* iter = _queue->head;
    while (iter != NULL) {
        if (iter->item == item) { return iter; }
        iter = iter->next;
    }
    return NULL;
}