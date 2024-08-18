#include <stdio.h>
#include <stdlib.h>


typedef struct heap {
	int* cnt;
	int size;
	int count;
} heap;

heap* makeHeap(int size) {
	heap* h = (heap*)malloc(sizeof(heap));
	h->cnt = (int*)malloc(sizeof(int) * size);
	h->size = size;
	h->count = 0;
	return h;
}

void printHeap(heap* h) {
    for (int i = 0; i < h->count; i++) {
        printf("%d\n", h->cnt[i]);
    }
}

int parent(unsigned int i) {
    if (i == 0) {
        return -1;
    }
    return (unsigned int) ((i - 1) / 2);
}

int leftChild(unsigned int i) {
    return (2 * i) + 1;
}

int rightChild(unsigned int i) {
    return 2 * (i + 1);
}

void swap(heap* h, int p1, int p2) {
    int tmp = h->cnt[p1];
    h->cnt[p1] = h->cnt[p2];
    h->cnt[p2] = tmp;
}

void bubble_up(heap* h, int p) {
    if (p == 0 || h->cnt[parent(p)] < h->cnt[p])
        return;
    else {
        swap(h, parent(p), p);
        bubble_up(h, parent(p));
    }
}

void bubble_down(heap* h, unsigned int p) {
    if (h->count <= leftChild(p)) {
        return;
    }
    if (h->count <= rightChild(p)) {
        if (h->cnt[p] > h->cnt[leftChild(p)]) {
            printf("Swap parent and left node\n");
            swap(h, p, leftChild(p));
        }
        return;
    }
    else if (h->cnt[leftChild(p)] < h->cnt[p] && h->cnt[leftChild(p)] < h->cnt[rightChild(p)]) {
        swap(h, leftChild(p), p);
        bubble_down(h, leftChild(p));
    }
    else if (h->cnt[rightChild(p)] < h->cnt[p] && h->cnt[rightChild(p)] < h->cnt[leftChild(p)]) {
        swap(h, p, rightChild(p));
        bubble_down(h, rightChild(p));
    }
}

heap* heapify(int nums[], int size) {
    int i;
    heap* h = makeHeap(size);

    for (i = 0; i < h->size; i++) {
        h->cnt[i] = nums[i];
        h->count++;
    }
        
    for (i = h->size - 1; i >= 0; i--) bubble_down(h, i);

    return h;
}

void insert(heap* h, int x) {
   if (h->count >= h->size) {
       return;
   }
   h->cnt[h->count] = x;
   bubble_up(h, h->count);
   h->count++;
}

int extractMin(heap* h) {
    if (h->count == 0) {
        return -1;
    }
    int min = h->cnt[0];
    h->cnt[0] = h->cnt[h->count - 1];
    h->count--;
    bubble_down(h, 0);
    return min;
}

void heapSort(int nums[], int numCount) {
    heap* h = makeHeap(numCount);

    for (int i = 0; i < numCount; i++) {
        insert(h, nums[i]);
    }

    for (int i = 0; i < numCount; i++) {
        nums[i] = extractMin(h);
    }
}
