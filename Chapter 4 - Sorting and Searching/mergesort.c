#include <stdio.h>
#include <stdlib.h>


void merge(int*, int, int, int);
void mergeSort(int*, int, int);


/* We'll need to use queues */
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
    if (_queue == NULL || _queue->head == NULL) { exit(1); } /* la file est vide */
    node* head = _queue->head;
    int headItem = head->item;

    _queue->head = _queue->head->next;
    if(_queue->head == NULL) {
        _queue->tail = NULL;
    }

    free(head);
    return headItem;
}

int emptyQueue(queue* q) {
    return (q == NULL || q->head == NULL || q->tail == NULL);
};

void initQueue(queue** q) {
    *q = (queue*)malloc(sizeof(queue));
    (*q)->head = NULL;
    (*q)->tail = NULL;
}

/* Main program */

void mergeSort(int arr[], int start, int end) {
    if (start < end) {
        int middle = (int) (start + end) / 2;
        mergeSort(arr, start, middle);
        mergeSort(arr, middle + 1, end);
        merge(arr, start, middle, end);
    }
}

void merge(int* arr, int start, int middle, int end) {
    printf("start = %d, end = %d\n", start, end);
    queue* left;
    queue* right;
    
    initQueue(&left);
    initQueue(&right);

    int i;
    for (i = start; i <= middle; i++) {
        enqueue(arr[i], left);
    }
    for (i = middle + 1; i <= end; i++) {
        enqueue(arr[i], right);
    }
    
    i = start;
    while (!emptyQueue(left) && !emptyQueue(right)) {
        if (left->head->item < right->head->item) arr[i++] = dequeue(left);
        else arr[i++] = dequeue(right);
    }
    while (!emptyQueue(left)) { arr[i++] = dequeue(left); }
    while (!emptyQueue(right)) { arr[i++] = dequeue(right); }
}


void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++)
        printf("%d\n", arr[i]);
}

int main(void) {
    int arr[] = {4, 1, 0, 3, 7, 9, 8, 2, 6, 5};
    mergeSort(arr, 0, 9);
    printArray(arr, 10);
    return 0;
}
