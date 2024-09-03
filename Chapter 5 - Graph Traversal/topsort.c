#include <stdlib.h>
#include <stdio.h>

#include "stack.h"


stack* s;
state* states;
int* parent;
int * entry;
int dfs_time = 0;

void dfs(graph*, int);
void topological_sort(graph*);
void init_dfs(graph*);

void init_dfs(graph* g) {
    init_stack(&s);
    states = (state*)malloc(sizeof(state) * g->nvertices);
    parent = (int*)malloc(sizeof(int) * g->nvertices);
    entry = (int*)malloc(sizeof(int) * g->nvertices);

    for (int i = 0; i < g->nvertices; i++) {
        states[i] = UNDISCOVERED;
        parent[i] = -1;
        entry[i] = dfs_time;
    }
}

void topological_sort(graph* g) {

    if ( !(g->directed) ) {
        printf("The graph is undirected\n");
        return;
    }

    int u; /* iterator */

    init_dfs(g);

    for (u = 0; u < g->nvertices; u++) {
        if (states[u] == UNDISCOVERED) {
            dfs(g, u);
        }
    }
    print_stack(s);
}


void dfs(graph* g, int u) {
    edgenode* p = (edgenode*)malloc(sizeof(edgenode));

    states[u] = DISCOVERED;
    entry[u] = dfs_time++;

    p = g->edges[u];
    while (p != NULL) {
        
        if (states[p->y] == UNDISCOVERED) {
            parent[p->y] = u;
            dfs(g, p->y);
        }
        else if (states[p->y] == DISCOVERED && parent[u] != p->y) {
            printf("Back Edge Found. Not a DAG\n");
            return;
        }
        p = p->next;
    }

    states[u] = PROCESSED;
    push(&s, u);
}
