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
}

void process_vertex_late(int vertex) {
}

void find_path(int start, int end) {
    if (start == end || end == -1) {
        printf(" %d", end);
    } else {
        find_path(start, parent[end]);
        printf(" %d", end);
    }
}

void process_edge(int x, int y) {
    if (state[y] == DISCOVERED && parent[x] != y) {
        printf("\nCycle:");
        find_path(y, x);
    }
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
            parent[p->y] = vertex;
            dfs(g, p->y);
        } else {
            process_edge(vertex, p->y);
        }

        if (finished) return;
        
        p = p->next;
    }
    process_vertex_late(vertex);
    state[vertex] = PROCESSED;

    exit_time[vertex] = dfs_time;
    dfs_time++;
}

void find_cycles(graph* g) {
    for (int i = 0; i < (g->nvertices); ++i) {
        if (state[i] == UNDISCOVERED)
            dfs(g, i);
    }   
}


int main(void) {
    graph* g;
    
    read_graph(&g, TRUE);
    init_search(g);

    find_cycles(g);
    printf("\n");
    return 0;
}
