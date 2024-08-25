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
    // printf("%d ", y);
}


bool process_vertex(int vID, int goal) {
    return vID == goal;
}

int* bfs(graph* g, int start, int goal) {
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
        if (process_vertex(vID, goal) == TRUE ) {
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


void shortest_path(int* parent_tree, int goal) {
    if (parent_tree == NULL || goal == -1) return;

    shortest_path(parent_tree, parent_tree[goal]);
    printf("%d -> ", goal);
}


int main() {
    graph* g;
    read_graph(&g, TRUE);

    int* parent_tree = bfs(g, 0, 5);
    shortest_path(parent_tree, 5);
    printf("\n");

    return 0;
}
