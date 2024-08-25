#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "BFS_search.h"


void init_search(state *states, int* bfs_tree, int nvertices) {
    for (int i = 0; i < nvertices; i++) {
        states[i] = UNDISCOVERED;
        bfs_tree[i] = -1;
    }
}


void process_edge(int x, int y) {
    printf("%d ", y);
}


void process_vertex(int vID) {
    printf("Vertex %d: ", vID);
}

int* bfs(graph* g, int start) {
    queue* q;                                   /* queue structure */
    int vID;                                    /* iterator for vertices */
    edgenode* adj = malloc(sizeof(edgenode));   /* iterates over adjacent vertices of a vertex */
    
    state states[g->nvertices];
    int* bfs_tree = (int*)malloc(sizeof(int) * g->nvertices);

    init_search(states, bfs_tree, g->nvertices);
    init_queue(&q);

    states[start] = DISCOVERED;
    enqueue(q, start);

    while ( empty(q) == FALSE) {
        vID = dequeue(q);
        process_vertex(vID);   /* process vertex */
        
        adj = g->edges[vID];
        while (adj != NULL) {
            process_edge(vID, adj->y);
            if (states[adj->y] == UNDISCOVERED) {
                states[adj->y] = DISCOVERED;
                bfs_tree[adj->y] = vID;
                enqueue(q, adj->y);
            }
            adj = adj->next;
        }
        states[vID] = PROCESSED;
        printf("\n");
    }

    return bfs_tree;
}


int main() {
    graph* g;
    read_graph(&g, TRUE);

    bfs(g, 0);

    return 0;
}
