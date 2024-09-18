#include <stdlib.h>

#include "graph.h"


void init_graph(graph** g, int nvertices, bool directed) {
    *g = (graph*)malloc(sizeof(graph));
    (*g)->edges = (edgenode**)malloc(sizeof(edgenode*) * nvertices);
    (*g)->degree = (int*)malloc(sizeof(nvertices));
    (*g)->nvertices = nvertices;
    (*g)->nedges = 0;
    (*g)->directed = directed;

    for (int i = 0;i < nvertices; i++) {
        (*g)->edges[i] = NULL;
        (*g)->degree[i] = 0;
    }
}


bool is_edge(graph* g, int x, int y) {
    edgenode* p = g->edges[x];
    
    while (p != NULL) {
        if (p->y == y)
            return TRUE;
        p = p->next;
    }
    return FALSE;
}


void insert_edge(graph* g, int x, int y, int weight) {
    edgenode* p = (edgenode*)malloc(sizeof(edgenode));
    p->y = y;
    p->weight = weight;
    p->next = g->edges[x];
    g->edges[x] = p;
    g->degree[x]++;
    g->nedges++;

    if (g->directed == FALSE && is_edge(g, y, x) == FALSE) 
        insert_edge(g, y, x, weight);
}


void read_graph(graph** g, bool directed) {
    int x, y, w = 0;
    int nvertices, nedges;

    printf("Give the number of vertices and edges\n");
    scanf("%d %d", &nvertices, &nedges);

    init_graph(g, nvertices, directed);

    printf("\nGive the list of edges one per line (x, y, w)\n");
    for (int i = 0; i < nedges; i++) {
        printf("Edge %d: ", i+1);
        scanf("%d %d %d", &x, &y, &w);
        insert_edge(*g, x, y, w);
    }
}


void print_graph(graph* g) {
    int i;
    edgenode* p;

    for (i = 0; i < g->nvertices; i++) {
        printf("Vertex ID %d: ", i);
        p = g->edges[i];
        
        while (p != NULL) {
            printf("(%d, w = %d) ", p->y, p->weight);
            p = p->next;
        }
        printf("\n");
    }
}
