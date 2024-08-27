#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "BFS_search.h"


void process_vertex(int vID) {
    printf(" %d", vID);
}

void process_edge(int x, int y) {
    return;
}

void init_state(graph* g, state states[]) {
    for (int i = 0; i < (g->nvertices); i++)
        states[i] = UNDISCOVERED;
}

void BFS(graph* g, int root, state states[]) {
    queue* q;
    int vertexID;
    edgenode* adj_vertex = (edgenode*)malloc(sizeof(edgenode));

    init_queue(&q);

    if (states == NULL) {
        states = (state*)malloc(sizeof(state) * (g->nvertices));
        init_state(g, states);
    }

    states[root] = DISCOVERED;
    enqueue(q, root);
    
    while (empty(q) == FALSE) {
        vertexID = dequeue(q);
        process_vertex(vertexID);
        
        adj_vertex = g->edges[vertexID];

        while (adj_vertex != NULL) {
            process_edge(vertexID, adj_vertex->y);
            
            if (states[adj_vertex->y] == UNDISCOVERED) {
                states[adj_vertex->y] = DISCOVERED;
                enqueue(q, adj_vertex->y);
            }
            adj_vertex = adj_vertex->next;
        }
        states[vertexID] = PROCESSED;
    }
}

void connected_components(graph* g) {
    state* states = (state*)malloc(sizeof(state) * (g->nvertices));
    int component_count = 0;

    init_state(g, states);

    for (int i = 0; i < (g->nvertices); i++) {
        if (states[i] == UNDISCOVERED) {
            component_count++;
            printf("Component %d:", component_count);
            BFS(g, i, states);
            printf("\n");
        }
    }
    free(states);
}


int main(void) {
    graph* g;
    read_graph(&g, FALSE);
    connected_components(g);
    return 0;
}
