#include "graph.h"

struct heap {
    struct edge** array;
    int count;      /* number of elements */
    int size;       /* maximum number of elements */
};


void init_heap(struct heap**, int);
void insert_heap(struct heap*, struct edge*);
void bubble_up(struct heap*, int);
void bubble_down(struct heap*, int);
int empty_heap(struct heap*);
struct edge* extract_heap(struct heap*);
void swap(struct heap*, int, int);
int parent(int);
int left(int);
int right(int);
int compare(struct edge*, struct edge*);
