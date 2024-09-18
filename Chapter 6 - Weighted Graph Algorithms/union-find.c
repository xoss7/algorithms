#include <stdlib.h>

#include "union-find.h"


void init_union_set(struct union_set* set_partition, int partition_count) {
    set_partition->parent = (int*)malloc(sizeof(int) * partition_count);
    set_partition->size = (int*)malloc(sizeof(int) * partition_count);
    
    for (int i = 0; i < partition_count; ++i) {
        set_partition->parent[i] = i;
        set_partition->size[i] = 1;
    }
}   

int find(struct union_set* set_partition, int item) {
    if (set_partition->parent[item] == item)
        return item; 
    else 
        return find(set_partition, set_partition->parent[item]);
}

void merge(struct union_set* set_partition, int u, int v) {
    int repr_u = find(set_partition, u);
    int repr_v = find(set_partition, v);

    if (repr_u == repr_v)
        return;         /* u and v are already in the same class */
    
    /* merge the smaller partition to the bigger one */
    if (set_partition->size[repr_u] <= set_partition->size[repr_v]) {
        set_partition->parent[repr_u] = repr_v;
        set_partition->size[repr_v] += set_partition->size[repr_u];
    } else {
        set_partition->parent[repr_v] = repr_u;
        set_partition->size[repr_u] += set_partition->size[repr_v];
    }
}
