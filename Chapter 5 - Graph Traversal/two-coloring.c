#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "BFS_search.h"

typedef enum color {
    UNCOLORED,
    WHITE,
    BLACK
} color;

void process_vertex(int, color*);
bool process_edge(int, int, color*);
color complement(color);
bool bfs(graph*, int, state*, color*);
void init_state(state*, int);

void process_vertex(int vID, color colors[]) {
    if (colors[vID] == WHITE) {
        printf("vID %d: WHITE\n", vID);
    } else if (colors[vID] == BLACK) {
        printf("vID %d: BLACK\n", vID);
    } else {
        printf("vID %d: UNCOLORED\n", vID);
    }
}

bool process_edge(int parent, int vID, color colors[]) {
    if (colors[parent] == colors[vID]) {
        printf("Conflict on edge (%d, %d)\n", parent, vID);
        return TRUE;
    }

    colors[vID] = complement(colors[parent]);
    return  FALSE;
}

color complement(color col) {
    if (col == BLACK)   return WHITE;
    if (col == WHITE)   return BLACK;

    return UNCOLORED;
}

void init_state(state states[], int len) {
    
    for (int i = 0; i < len; i++)
        states[i] = UNDISCOVERED;
}

bool bfs(graph* g, int start, state states[], color colors[]) {
    edgenode* adj_vertex = (edgenode*)malloc(sizeof(edgenode));
    int vID;
    queue* q;
    init_queue(&q);

    if (states == NULL) {
        state* states = (state*)malloc(sizeof(state) * (g->nvertices));
        init_state(states, g->nvertices);
    }

    colors[start] = WHITE;
    states[start] = DISCOVERED;
    enqueue(q, start);

    while ( empty(q) == FALSE) {
        vID = dequeue(q);
        process_vertex(vID, colors);

        adj_vertex = g->edges[vID];
        while (adj_vertex != NULL) {
        
            if ( process_edge(vID, adj_vertex->y, colors) == TRUE)
                return FALSE;

            if (states[adj_vertex->y] == UNDISCOVERED) {
                states[adj_vertex->y] = DISCOVERED;
                enqueue(q, adj_vertex->y);
            }
            adj_vertex = adj_vertex->next;
        }
    }
    return TRUE;
}

void twocolor(graph* g) {
    color colors[g->nvertices];
    state states[g->nvertices];

    for (int i = 0; i < (g->nvertices); ++i)
        states[i] = UNDISCOVERED;

    for (int i = 0; i < (g->nvertices); i++)
        colors[i] = UNCOLORED;

    for (int i = 0; i < (g->nvertices); ++i) {
        
        if (states[i] == UNDISCOVERED) {
            if (bfs(g, i, states, colors) == FALSE) {
                return;
            }
        }
    }
}


int main(void) {
    graph* g;
    read_graph(&g, FALSE);
    twocolor(g);

    return 0;
}
