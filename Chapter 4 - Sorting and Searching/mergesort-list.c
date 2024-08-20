#include <stdlib.h>

/* Linked list definition */
typedef struct node {
    int item;
    struct node* next;
} node;

node* newList() {
    node* new = (node*)malloc(sizeof(node));
    new = NULL;
    return new;
}

void insert(node** list, int item) {
    node* new = (node*)malloc(sizeof(node));
    new->next = *list;
    new->item = item;
    *list = new;
}


void printList(node* list) {
    if (list == NULL)
        return;
    else {
        printf("%d -> ", list->item);
        printList(list->next);
    }
}

/* Merge sort */

void halveList(node* list, node** left, node** right) {
    node* slow = (node*)malloc(sizeof(node));
    node* fast = (node*)malloc(sizeof(node));

    *left = NULL;
    *right = NULL;

    if (list == NULL) return;
    
    *left = list;
    slow = list;
    fast = list->next;

    while(fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    *right = slow->next;
    slow->next = NULL;
}

node* merge(node* left, node* right) {
    node* head = (node*)malloc(sizeof(node));
    node* prev = (node*)malloc(sizeof(node));

    if (left == NULL) return right;
    if (right == NULL) return left;
    
    if (left->item < right->item) {
        head = left;
        prev = left;
        left = left->next;
    } else {
        head = right;
        prev = right;
        right = right->next;
    }

    while (left != NULL && right != NULL) {
        if (left->item < right->item) {
            prev->next = left;
            prev = left;
            left = left->next;
        } else {
            prev->next = right;
            prev = right;
            right = right->next;
        }
    }

    if (left != NULL) {
        prev->next = left;
    } else {
        prev->next = right;
    }
    return head;
}

void mergeSort(node** list) {
    node* left = (node*)malloc(sizeof(node));
    node* right = (node*)malloc(sizeof(node));

    if (*list == NULL || (*list)->next == NULL) return;

    halveList(*list, &left, &right);
    mergeSort(&left);
    mergeSort(&right);
    *list = merge(left, right);
}
