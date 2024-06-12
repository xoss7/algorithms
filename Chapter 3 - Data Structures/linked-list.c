#include <stdio.h>
#include <stdlib.h>

typedef struct  list
{
    int item;         /* data item */
    struct list* next;  /* point to successor */
} list;


/* searching a list */
list* search(list* _list, int item) {
    if (_list == NULL || _list->item == item) { return _list; }
    return search(_list->next, item);
}


/* Insertion into a list */
void insert(list** _list, int item) {
    list* new_l = (list*)malloc(sizeof(list));
    new_l->next = *_list;
    new_l->item = item;
    *_list = new_l;
}


/* Deletion from a list */
void delete(list** head, int item) {
    if (*head == NULL) { return; }
    if ((*head)->item == item) {
        list* tmp = *head;
        *head = (*head)->next;
        free(tmp);
        return;
    }
    delete(&((*head)->next), item);
}


/* print a list */
void printList(list* _list) {
    list* iter = _list;
    while (iter != NULL) {
        printf("%d -> ", iter->item);
        iter = iter->next;
    }
    printf("NULL\n");
}