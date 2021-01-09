#include "datastructs.h"
#include <stdlib.h>


/**
 * Queue
 */
struct queue *create_queue()
{
    return malloc(sizeof(queue_t));
}

void add_queue(queue_t *q, void *data)
{
    if (q->last == NULL)
        q->last = q->first = create_slnode(data);
    else {
        q->last->next = create_slnode(data);
        q->last = q->last->next;
    }
}

void pop_queue(queue_t *q, void *data)
{
    if (q->first == NULL) {
        data = NULL;
        return;
    }

    sl_node_t *tmp = q->first;
    q->first = q->first->next;

    data = tmp->data;
    free(tmp); // Regular free() as we return the data pointer
}

void free_queue(queue_t *q)
{
    free_slnode_seq(q->first);
    free(q);
}

/**
 * Queue - derived
 */

uint32_t count_queue(queue_t *s) 
{
    if (s->first == NULL)
        return 0;

    count_slnode_seq(s->first);
}

void map_queue(queue_t *q, void (*func)(sl_node_t *, void *))
{
    sl_node_t *n = q->first;
    while (n != NULL) {
        func(n, NULL);
        n = n->next;
    }
}
