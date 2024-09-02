#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

enum state {
    UNDISCOVERED,
    DISCOVERED,
    PROCESSED
};

int dfs_time = 0;
int finished = FALSE;
int* parent;
int* lowpoint;
int* entry_time;
int* tree_out_degree;
bool* cut_vertex;
enum state* state;


void init_search(graph* g) {
    parent = (int*)malloc(sizeof(int) * (g->nvertices));
    lowpoint = (int*)malloc(sizeof(int) * (g->nvertices));
    cut_vertex = (bool*)malloc(sizeof(bool) * (g->nvertices));
    tree_out_degree = (int*)malloc(sizeof(int) * (g->nvertices));
    entry_time = (int*)malloc(sizeof(int) * g->nvertices);
    state = (enum state*)malloc(sizeof(enum state) * g->nvertices);
    
    int i;
    for (i = 0; i < g->nvertices; ++i) {
        parent[i] = -1;
        entry_time[i] = dfs_time;
        cut_vertex[i] = FALSE;
        state[i] = UNDISCOVERED;
    }
}


void process_vertex_early(int vertex) {
    state[vertex] = DISCOVERED;
    entry_time[vertex] = dfs_time;
    lowpoint[vertex] = dfs_time;
}

void process_vertex_late(int vertex) {
    
    int root = (parent[vertex] == -1);
    if (root && tree_out_degree[vertex] > 1) {
        printf("root articulation point %d\n", vertex);
        cut_vertex[vertex] = TRUE;
    }
    state[vertex] = PROCESSED;
}

void process_edge(int x, int y) {
}

void dfs(graph* g, int vertex) { 
    edgenode* p = (edgenode*)malloc(sizeof(edgenode));

    process_vertex_early(vertex);
    dfs_time++;

    p = g->edges[vertex];
    while (p != NULL) {

        if (state[p->y] == UNDISCOVERED) {
            parent[p->y] = vertex;
            tree_out_degree[vertex]++;
            dfs(g, p->y);
            
            if (parent[vertex] != -1 && lowpoint[p->y] >= entry_time[vertex]) {
                cut_vertex[vertex] = TRUE;
                printf("articulation point %d\n", vertex);
            }
            lowpoint[vertex] = lowpoint[vertex] < lowpoint[p->y] ? lowpoint[vertex] : lowpoint[p->y];
        } else if (state[p->y] == DISCOVERED && parent[vertex] != p->y) {
            lowpoint[vertex] = lowpoint[vertex] < entry_time[p->y] ? lowpoint[vertex] : entry_time[p->y];
        }

        if (finished) return;
        
        p = p->next;
    }

    process_vertex_late(vertex);
}

int main(int argc, char** argv) {
    graph* g;
    
    read_graph(&g, FALSE);
    init_search(g);
    dfs(g, atoi(argv[1]));
    printf("\n");
    return 0;
}
