#include <stdlib.h>
#include <stdio.h>

#include "union-find.h"
#include "heap.h"

int cost = 0;

void heap_sort(graph* g, struct heap* p_queue) {
    edgenode* p;        /* adjacent vertex */
    struct edge* edge;  /* Edge from graph */
    int visited[g->nvertices];

    for (int i = 0; i < g->nvertices; i++) {
        visited[i] = 0;
    }

    for (int u = 0; u < (g->nvertices); u++) {
        p = g->edges[u];

        while (p != NULL) {
            if ( !visited[p->y] ) {
                edge = malloc(sizeof(struct edge));
                edge->u = u;
                edge->v = p->y;
                edge->weight = p->weight;
                insert_heap(p_queue, edge);
            }
            p = p->next;
        }
        visited[u] = 1;
    }
}

int same_component(struct union_set* s, int u, int v) {
    return find(s, u) == find(s, v);
}

struct edge** kruskal(graph* g) {
    struct edge** mst;   /* minimum spanning tree */
    struct edge* edge;  /* next edge of minimum weight */
    struct heap* p_queue;   /* priority queue of edges with weight as key */
    struct union_set* partition_set;

    mst = malloc(sizeof(struct edge*) * ((g->nvertices)-1));
    edge = malloc(sizeof(struct edge));
    partition_set = malloc(sizeof(struct union_set));
    
    init_union_set(partition_set, g->nvertices);
    init_heap(&p_queue, g->nedges);
    
    heap_sort(g, p_queue);

    int count = 0;
    cost = 0;
    while ( !empty_heap(p_queue) ) {
        edge = extract_heap(p_queue);
        if ( !same_component(partition_set, edge->u, edge->v) ) {
            printf("%d\n", edge->weight);
            mst[count++] = edge;
            cost += edge->weight;
            merge(partition_set, edge->u, edge->v);
        }
    }
    return mst;
}


int main(void) {
    graph* g;
    read_graph(&g, FALSE);
    
    struct heap* pq;
    init_heap(&pq, g->nedges);
    heap_sort(g, pq);
    
    struct edge** ms_tree = kruskal(g);

    for (int i = 0; i < (g->nvertices - 1); i++) {
        printf("(%d, %d, %d)\n", ms_tree[i]->u, ms_tree[i]->v, ms_tree[i]->weight);
    }
    printf("cost = %d\n", cost);
    return 0;
}
