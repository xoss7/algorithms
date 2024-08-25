#include <stdlib.h>
#include <stdio.h>

#include "queue.h"


bool empty(queue* q) {
    return (q->front == NULL || q->tail == NULL);
}


void init_queue(queue** q) {
    *q = (queue*)malloc(sizeof(queue));
    (*q)->front = NULL;
    (*q)->tail = NULL;
}


void enqueue(queue* q, int vID) {
    node* p = (node*)malloc(sizeof(node));
    p->vID = vID;
    p->next = NULL;

    if ( empty(q) ) {
        q->front = p;
        q->tail = p;
    } else {
        q->tail->next = p;
        q->tail = p;
    }
}


int dequeue(queue* q) {
    int vID = -1;
    node* p;
    if ( empty(q) == FALSE) {
        p = q->front;
        q->front = q->front->next;
        vID = p->vID;
        free(p);
    }
    return vID;
}


void print_queue(queue* q) {
    
    if ( empty(q) == FALSE) {
        node* p = q->front;

        while (p != NULL) {
            printf("%d ", p->vID);
            p = p->next;
        }
        printf("\n");
    }
}
