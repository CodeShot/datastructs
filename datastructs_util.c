#include "datastructs.h"
#include <stdio.h>


/**
 * Printing functions
 */
void print_data(void *ndata, void *fdata)
{
    printf("%c", *(char *)ndata);
}

void print_stack(stack_t *s)
{
    map_slnode_data_seq(s->first, print_data, NULL);
}

void print_queue(queue_t *q)
{
    map_slnode_data_seq(q->first, print_data, NULL);
}

void print_deque(deque_t *dq, bool reverse)
{
    dl_node_t *n = dq->first;

    if (reverse) 
        n = dq->last;

    map_dlnode_data_seq(n, print_data, NULL, reverse);
}

/**
 *
 */
