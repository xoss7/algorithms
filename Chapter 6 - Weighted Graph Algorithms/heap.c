#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

void init_heap(struct heap** heap, int size) {
    *heap = (struct heap*)malloc(sizeof(struct heap));
    (*heap)->array = (struct edge**)malloc(sizeof(struct edge*) * size);
    (*heap)->size = size;
    (*heap)->count = 0;
}


int parent(int p) {
    return (--p / 2);
}


int left(int p) {
    return (2 * p + 1);
}


int right(int p) {
    return (2 * p + 2);
}


int compare(struct edge* edge1, struct edge * edge2) {
    if (edge1->weight < edge2->weight) {
        return -1;
    } else if (edge1->weight > edge2->weight) {
        return 1;
    } else {
        return 0;
    }
}


void swap(struct heap* heap, int p1, int p2) {
    struct edge* edge = heap->array[p1];
    heap->array[p1] = heap->array[p2];
    heap->array[p2] = edge;
}


void bubble_up(struct heap* heap, int p) {
    
    if (p == 0)
        return;

    if ( compare(heap->array[p], heap->array[parent(p)]) == -1 ) {
        swap(heap, p, parent(p));
        bubble_up(heap, parent(p));
    }
}


void bubble_down(struct heap* heap, int p) {
    int min_child;
    min_child = p;

    if (right(p) < heap->count) {

        if ( compare(heap->array[left(p)], heap->array[right(p)]) == -1 ) {
            min_child = left(p);
        } else if ( compare(heap->array[left(p)], heap->array[right(p)]) == 1) {
            min_child = right(p);
        }

    } else if (left(p) < heap->count) {
        min_child = left(p);
    }

    if ( compare(heap->array[min_child], heap->array[p]) == -1 ) {
        swap(heap, p, min_child);
        bubble_down(heap, min_child);
    }
}


int empty_heap(struct heap* heap) {
    return (heap->count == 0);
}

void insert_heap(struct heap* heap, struct edge* edge) { 
    if (heap->count < heap->size) {
        heap->array[heap->count] = edge;
        heap->count++;
        bubble_up(heap, heap->count-1);
    }
}


struct edge* extract_heap(struct heap* heap) {
    
    if (empty_heap(heap)) {
        return NULL;
    }

    struct edge* edge = heap->array[0];
    heap->count -= 1;
    heap->array[0] = heap->array[heap->count];
    bubble_down(heap, 0);

    return edge;
}
