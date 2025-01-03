#include "pq.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct ListElement ListElement;

struct ListElement {
    Node *tree;
    ListElement *next;
};
struct PriorityQueue {
    ListElement *list;
};

PriorityQueue *pq_create(void) {
    PriorityQueue *pq = calloc(1, sizeof(PriorityQueue));
    return pq;
}

void pq_free(PriorityQueue **q) {
    free(*q);
    *q = NULL;
}

bool pq_is_empty(PriorityQueue *q) {
    return q->list == NULL;
}

bool pq_size_is_1(PriorityQueue *q) {
    if (pq_is_empty(q)) {
        return false;
    }
    int counter = 1;
    ListElement *temp = q->list;
    while (temp->next != NULL) {
        counter++;
        temp = temp->next;
    }
    if (counter > 1) {
        return false;
    }
    return true;
}

bool pq_less_than(Node *n1, Node *n2) {
    if (n1->weight < n2->weight)
        return true;
    if (n1->weight > n2->weight)
        return false;
    return n1->symbol < n2->symbol;
}

void enqueue(PriorityQueue *q, Node *tree) {
    ListElement *e = calloc(1, sizeof(ListElement));
    e->tree = tree;
    if (pq_is_empty(q)) {
        q->list = e;
    } else if (pq_less_than(e->tree, q->list->tree)) {
        e->next = q->list;
        q->list = e;
    } else {
        ListElement *temp = q->list;
        while (temp->next != NULL && pq_less_than(temp->next->tree, e->tree)) {
            temp = temp->next;
        }
        e->next = temp->next;
        temp->next = e;
    }
}

bool dequeue(PriorityQueue *q, Node **tree) {
    if (pq_is_empty(q)) {
        return false;
    } else {
        ListElement *e;
        e = q->list;
        q->list = q->list->next;
        *tree = e->tree;
        free(e);
        return true;
    }
}

void pq_print(PriorityQueue *q) {
    assert(q != NULL);
    ListElement *e = q->list;
    int position = 1;
    while (e != NULL) {
        if (position++ == 1) {
            printf("=============================================\n");
        } else {
            printf("---------------------------------------------\n");
        }
        node_print_tree(e->tree, '<', 2);
        e = e->next;
    }
    printf("=============================================\n");
}
