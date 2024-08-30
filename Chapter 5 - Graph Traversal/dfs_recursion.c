#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

enum state {
    UNDISCOVERED,
    DISCOVERED,
    PROCESSED
};

int dfs_time = 0;
int finished = 0;
int* parent;
int* entry_time;
int* exit_time;
enum state* state;


void init_search(graph* g) {
    parent = (int*)malloc(sizeof(int) * (g->nvertices));
    entry_time = (int*)malloc(sizeof(int) * g->nvertices);
    exit_time = (int*)malloc(sizeof(int) * g->nvertices);
    state = (enum state*)malloc(sizeof(enum state) * g->nvertices);
    
    int i;
    for (i = 0; i < g->nvertices; ++i) {
        parent[i] = -1;
        entry_time[i] = 0;
        exit_time[i] = 0;
        state[i] = UNDISCOVERED;
    }
}


void process_vertex_early(int vertex) {
    printf("%d\n", vertex);
}

void process_vertex_late(int vertex) {

}

void process_edge(int x, int y) {
    printf("edge (%d, %d)\n", x, y);
}

void dfs(graph* g, int vertex) { 
    edgenode* p = (edgenode*)malloc(sizeof(edgenode));

    state[vertex] = DISCOVERED;
    entry_time[vertex] = dfs_time;
    dfs_time++;

    process_vertex_early(vertex);

    p = g->edges[vertex];
    while (p != NULL) {
        
        if (state[p->y] == UNDISCOVERED) {
            process_edge(vertex, p->y);
            parent[p->y] = vertex;
            dfs(g, p->y);
        } else if (state[p->y] != PROCESSED || g->directed) {
            process_edge(vertex, p->y);

            if (finished) return;
        }

        if (finished) return;
        
        p = p->next;
    }
    process_vertex_late(vertex);
    state[vertex] = PROCESSED;

    exit_time[vertex] = dfs_time;
    dfs_time++;
}
