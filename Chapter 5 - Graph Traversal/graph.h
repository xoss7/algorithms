typedef enum bool {
    FALSE = 0,
    TRUE = 1 
} bool;


typedef struct edgenode {
    int y;                      /* node id of an edge */
    int weight;                 /* weight of the edge, if any */
    struct edgenode* next;      /* next edge */
} edgenode;


typedef struct graph {
    edgenode** edges;           /* array of edges of the graph */
    int* degree;                /* out-degree of eache vertex */
    int nvertices;              /* current number of vertices of the graph */
    int nedges;                 /* current number of edges in the graph */
    bool directed;              /* whether the graph is directed */
} graph;


void init_graph(graph**, int, bool);
void insert_edge(graph*, int, int, int);
bool is_edge(graph*, int, int);
void read_graph(graph**, bool);
void print_graph(graph*);
