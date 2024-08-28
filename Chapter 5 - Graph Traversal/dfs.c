#include <stdio.h>
#include <stdlib.h>

#include "stack.h"


void init_search(int parent[], state state_arr[], int nvertices) {
    int i;

    for (i = 0; i < nvertices; ++i) {
        parent[i] = -1;
        state_arr[i] = UNDISCOVERED;
    }
}


void process_vertex(int vertex) {
    printf("Vertex %d", vertex);
}

void process_edge(int v1, int v2) {
    printf(" %d", v2);
}

void dfs(graph* g, int start) {
    stack* s;   /* stack container */
    int vertex; /* ID of vertex being processed */
    edgenode* adj; /* iterator to adjacent nodes */

    int parent[g->nvertices];
    state state_arr[g->nvertices];

    init_stack(&s);
    init_search(parent, state_arr, g->nvertices);

    state_arr[start] = DISCOVERED;
    push(&s, start);

    while ( empty(s) == FALSE ) {
        vertex = pop(&s);
        process_vertex(vertex);

        adj = g->edges[vertex];
        
        while (adj != NULL) {
            //process_edge(vertex, adj->y);

            if (state_arr[adj->y] == UNDISCOVERED) {
                state_arr[adj->y] = DISCOVERED;
                parent[adj->y] = vertex;
                push(&s, adj->y);
            }
            adj = adj->next;
        }
        state_arr[vertex] = PROCESSED;
        printf("\n");
    }
}


int main(void) {
    graph* g;
    read_graph(&g, FALSE);
    printf("\n******* DFS *******\n");
    dfs(g, 0);

    return 0;
}
