#include <stdio.h>
#include <stdlib.h>

#include "stack.h"


stack* s;
int dfs_time = 0;
int component_id = 0;
int* parent;
int* lowlink;
int* entry_time;
int* scc;
state* states;

void init_dfs(graph*);
void strong_connect(graph*);
void dfs(graph*, int);

void init_dfs(graph* g) {
    init_stack(&s);
    parent = (int*)malloc(sizeof(int) * g->nvertices);
    entry_time = (int*)malloc(sizeof(int) * g->nvertices);
    lowlink = (int*)malloc(sizeof(int) * g->nvertices);
    scc = (int*)malloc(sizeof(int) * g->nvertices);

    states = (state*)malloc(sizeof(state) * g->nvertices);

    for (int i = 0; i < (g->nvertices); i++) {
        parent[i] = -1;
        states[i] = UNDISCOVERED;
        scc[i] = -1;
    }
}


void strong_connect(graph* g) {

    init_dfs(g);
    
    for (int i = 0; i < (g->nvertices); i++) {
        if (states[i] == UNDISCOVERED)
            dfs(g, i);
    }
}


void dfs(graph* g, int u) {
    edgenode* p = (edgenode*)malloc(sizeof(edgenode));
    int t;  /* store the popped value from the stack */

    states[u] = DISCOVERED;
    entry_time[u] = dfs_time;
    lowlink[u] = dfs_time++;
    push(&s, u);
    
    p = g->edges[u];

    while (p != NULL) {
        if (states[p->y] == UNDISCOVERED) {
            parent[p->y] = u;
            dfs(g, p->y);
            lowlink[u] = lowlink[u] < lowlink[p->y] ? lowlink[u] : lowlink[p->y];
        }
        else if (scc[p->y] == -1) { /* p->y is not assigned a component */
            lowlink[u] = lowlink[u] < entry_time[p->y] ? lowlink[u] : entry_time[p->y];
        }

        p = p->next;
    }

    if (lowlink[u] == entry_time[u]) {
        t = pop(&s);
        scc[t] = ++component_id;

        printf("compnent %d: %d", component_id, t);
        
        while (t != u) {
            t = pop(&s);
            scc[t] = component_id;

            printf(" %d", t);
        }
        printf("\n");
    }
}


int main(void) {
    graph* g;
    read_graph(&g, TRUE);
    strong_connect(g);
    return 0;
}
