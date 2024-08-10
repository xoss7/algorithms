#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


typedef struct tree
{
    int item;
    struct tree* parent;
    struct tree* right;
    struct tree* left;
} tree;


void traverseTree(tree* t) {
    if (t == NULL) { return; }

    printf("%d  ", t->item);
    traverseTree(t->left);
    traverseTree(t->right);
}

tree* minimum(tree* t) {
    if (t == NULL) { return NULL; }
    if (t->left == NULL) { return t; }
    return minimum(t->left);
}

void insert(tree** t, int item, tree* parent) {
    if (*t == NULL) {
        *t = (tree*)malloc(sizeof(tree));
        (*t)->item = item;
        (*t)->left = (*t)->right = NULL;
        (*t)->parent = parent;
        return;
    }

    if(item < (*t)->item)
        insert(&((*t)->left), item, *t);
    else if (item > (*t)->item)
        insert(&((*t)->right), item, *t);
}

tree* search(tree* t, int item) {
    if (t == NULL)
        return NULL;
    else if (t->item == item)
        return t;
    else if (t->item < item)
        return search(t->right, item);
    else
        return search(t->left, item);
}


void delete(tree** t, int item) {
    if (*t) {
        if (item < (*t)->item)
            delete(&((*t)->left), item);
        else if (item > (*t)->item) 
            delete(&((*t)->right), item);
        else {
            if ((*t)->left == NULL && (*t)->right == NULL) {
                *t = NULL;
                free(*t);
            }
            else if ((*t)->left == NULL && (*t)->right != NULL) {
                (*t)->right->parent = (*t)->parent;
                if (*t == (*t)->parent->right)
                    (*t)->parent->right = (*t)->right;
                else
                    (*t)->parent->left = (*t)->right;
                free(*t);
            }
            else if ((*t)->right == NULL && (*t)->left != NULL) {
                (*t)->left->parent = (*t)->parent;
                if(*t == (*t)->parent->right)
                    (*t)->parent->right = (*t)->left;
                else
                    (*t)->parent->left = (*t)->left;
                free(*t);
            }
            else {
                tree** s = (tree**)malloc(sizeof(tree*));
                *s = (tree*)malloc(sizeof(tree));
                *s = minimum((*t)->right);
                (*t)->item = (*s)->item;
                delete(s, (*s)->item);
            }
        }        
    }
}