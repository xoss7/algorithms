struct union_set {
    int* parent;        /* forest := parent of node i*/
    int* size;          /* number of children of subtree i */
};

void init_union_set(struct union_set*, int);    /* intialize the fields of the union set */
int find(struct union_set*, int);               /* returns the class of an item */
void merge(struct union_set*, int, int);        /* merge 2 classes into one */
