#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "queue.h"
#include "BFS_search.h"


void init_search(state *states, int* bfs_tree, int nvertices) {
    for (int i = 0; i < nvertices; i++) {
        states[i] = UNDISCOVERED;
        bfs_tree[i] = -1;
    }
}


void process_edge(int x, int y) {
    // printf("%d ", y);
}


bool process_vertex(int vID, int end) {
    return vID == end;
}

int* bfs(graph* g, int start, int end) {
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
        if (process_vertex(vID, end) == TRUE ) {
            break;
        }/* process vertex */
        
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


void shortest_path(int* parent_tree, int start, int end) {
    if (start != end && parent_tree[end] == -1)
        printf("Path from %d to %d not found\n", start, end);
    else if (start == end)
        printf("%d", end);
    else {
        shortest_path(parent_tree, start, parent_tree[end]);
        printf(" -> %d", end);
    }
}


int main() {
    graph* g;
    read_graph(&g, FALSE);

    int* parent_tree = bfs(g, 0, 4);
    shortest_path(parent_tree, 0, 4);
    printf("\n");

    return 0;
}
