#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "graph.h"


int* parent;          /* := shotest paths */
int* known;         /* := relaxed vertices */
int* distance;      /* := shortest distances */


void initialize(graph* g, int start) {
    parent = (int*)malloc(g->nvertices * sizeof(int));
    known = (int*)malloc(g->nvertices * sizeof(int));
    distance = (int*)malloc(g->nvertices * sizeof(int));

    int i;
    for (i = 0; i < g->nvertices; i++) {
        distance[i] = INT_MAX;
        known[i] = 0;
    }
    parent[start] = -1;
    distance[start] = 0;
}


void relax(graph* g, int u) {
    edgenode* p = (edgenode*)malloc(sizeof(edgenode));
    p = g->edges[u];

    while (p != NULL) {
        if (distance[p->y] > distance[u] + p->weight) {
            distance[p->y] = distance[u] + p->weight;
            parent[p->y] = u;
        }
        p = p->next;
    }
}


int extract_min(graph* g) {
    int i, v;
    int min = INT_MAX;

    for (i = 0; i < g->nvertices; i++) {
        if (!known[i] && distance[i] < min) {
            v = i;
            min = distance[i];
        }
    }
    return v;
}


void dijkstra_stp(graph* g, int start, int target) {
    int last;
    int next;

    initialize(g, start);
    relax(g, start);
    known[start] = 1;
    last = start;
    while (last != target) {
        next = extract_min(g);
        relax(g, next);
        known[next] = 1;
        last = next;
    }
}


void print_path(int target) {
    if (parent[target] == -1) {
        printf("%d", target);
    } else {
        print_path(parent[target]);
        printf(" -> %d", target);
    }
}
