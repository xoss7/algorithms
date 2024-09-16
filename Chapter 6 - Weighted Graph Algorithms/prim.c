#include "heap.h"

#include <stdlib.h>
#include <stdio.h>

int cost = 0;
int* tree;          /* spanning tree */
int* intree;        /* is vertex in ST ? */
struct heap* heap;  /* min heap of edges */
struct edge* edge;  /* edge structure (u, v, weight) */

void init(graph* g) {
    init_heap(&heap, g->nedges);
    tree = (int*)malloc(sizeof(int) * g->nvertices);
    intree = (int*)malloc(sizeof(int) * g->nvertices);

    for (int i = 0; i < g->nvertices; i++) {
        tree[i] = -1;
        intree[i] = 0;
    }
}


void process_vertex(graph* g, int i) {
    edgenode* p = g->edges[i];
    
    while ( p != NULL ) {
        if ( !intree[p->y] ) {
            edge = (struct edge*)malloc(sizeof(struct edge));
            edge->u = i;
            edge->v = p->y;
            edge->weight = p->weight;
            insert_heap(heap, edge);
        }
        p = p->next;
    }
}


void prim(graph* g, int start) {
    int i; /* vertex id */
    struct edge* e;    /* tmp variable */

    init(g);

    intree[start] = 1;
    process_vertex(g, start);

    while ( !empty_heap(heap) ) {
        e = extract_heap(heap);

        if ( !intree[e->v] ) {
            intree[e->v] = 1;
            tree[e->v] = e->u;
            cost += e->weight;
            process_vertex(g, e->v);
        }
    }
}

int main(void) {
    graph* g;
    read_graph(&g, FALSE);
    prim(g, 0);
    
    printf("Cost = %d\n", cost);
    for (int i = 0; i < g->nvertices; i++) {
        printf("parent(%d) = %d\n", i, tree[i]);
    }
    return 0;
}
