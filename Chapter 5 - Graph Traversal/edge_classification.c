enum edge_class {
    TREE,
    BACK,
    FORWARD,
    CROSS,
    UNDEFINED
};

enum state {
    UNDISCOVERED,
    DISCOVERED,
    PROCESSED
};

enum edge_class get_edge_class(int u, int v, int entry[], enum state state[]) {
    if (state[v] == UNDISCOVERED)
        return (TREE);
    if (state[v] == DISCOVERED)
        return (BACK);
    if (state[v] == PROCESSED && entry[u] < entry[v])
        return (FORWARD);
    if (state[v] == PROCESSED && entry[u] > entry[v])
        return (CROSS);
    return UNDEFINED;
}
