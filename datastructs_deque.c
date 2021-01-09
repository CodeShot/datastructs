#include "datastructs.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * Deque
 */
deque_t *create_deque()
{
    deque_t *dq = malloc(sizeof(deque_t));
    dq->count = 0;
    return dq;
}

void add_first_deque(deque_t *dq, void *data)
{
    dl_node_t *n = create_dlnode(data);
    
    if (dq->count == 0)
        dq->first = n;
    else if (dq->count == 1) {
        n->next = dq->last = dq->first;
        dq->first = dq->last->prev = n;
    }
    else {
        n->next = dq->first;
        dq->first = dq->first->prev = n;
    }

    dq->count++;
}

void add_last_deque(deque_t *dq, void *data)
{
    dl_node_t *n = create_dlnode(data);

    if (dq->count == 0)
        dq->first = n;
    else if (dq->count == 1) {
        dq->last = n;
        dq->last->prev = dq->first;
        dq->first->next = dq->last;
    }
    else {
        n->prev = dq->last;
        dq->last->next = n;
        dq->last = n;
    }

    dq->count++;
}

void pop_first_deque(deque_t *dq, void *data)
{
    if (dq->first == NULL) {
        data = NULL;
        return;
    }

    dl_node_t *n = dq->first;
    dq->first = dq->first->next;
    
    dq->count--;
    data = n->data;
    
    free(n);
}

void pop_last_deque(deque_t *dq, void *data)
{
    if (dq->last == NULL) {
        data = NULL;
        return;
    }

    dl_node_t *n = dq->last;
    dq->last = dq->last->prev;

    dq->count--;
    data = n->data;
    
    free(n);
}

void *contains_deque(deque_t *dq)
{
    dl_node_t *n = dq->last;
    dq->last = dq->last->prev;
    return n->data;
}

void free_deque(deque_t *dq)
{
    free_dlnode_seq(dq->first);
    free(dq);
}


/**
 * Queue - derived
 */

uint32_t count_deque(deque_t *dq) 
{
    if (dq->first == NULL)
        return 0;

    count_dlnode_seq(dq->first, 0);
}

void map_deque(deque_t *dq, void (*func)(dl_node_t *, void *), void *func_data, bool reverse)
{
    dl_node_t *start;

    if (reverse)
        start = dq->last;
    else
        start = dq->first;

    map_dlnode_seq(dq->last, func, func_data, reverse); 
}
