#include "datastructs.h"
#include <stdlib.h>


/**
 * Node types, core
 */
sl_node_t *create_slnode(void *const data) 
{
    struct sl_node *n = malloc(sizeof(*n));
    n->data = data;
    return n;
}

dl_node_t *create_dlnode(void *const data) 
{
    struct dl_node *n = malloc(sizeof(*n));
    n->data = data;
    return n;
}

dlp_node_t *create_dlpnode(void *const data) 
{
    struct dlp_node *n = malloc(sizeof(*n));
    n->data = data;
    return n;
}

void free_slnode(sl_node_t *n)
{
    free(n->data);
    free(n);
}

void free_dlnode(dl_node_t *n)
{
    free(n->data);
    free(n);
}

void free_dlpnode(dlp_node_t *n)
{
    free(n->data);
    free(n);
}

/**
 * Node types, derived
 */
void free_slnode_seq(sl_node_t *n)
{
    struct sl_node *tmp;

    while (n != NULL) {
        tmp = n->next;
        free(n);
        n = tmp;
    }
}

void free_dlnode_seq(dl_node_t *n)
{
    struct dl_node *tmp;

    while (n != NULL) {
        tmp = n->next;
        free(n);
        n = tmp;
    }
}

void map_slnode_seq(sl_node_t *const node, void (*func)(sl_node_t *, void *), void *func_data)
{
    sl_node_t *n = node;
    while (n != NULL) {
        func(n, NULL);
        n = n->next;
    }
}

void map_dlnode_seq(dl_node_t *const node, void (*func)(dl_node_t *, void *), void *func_data, bool reverse)
{
    dl_node_t *n = node;
    if (reverse) 
        while (n != NULL) {
            func(n, func_data);
            n = n->prev;
        }

    else 
        while (n != NULL) {
            func(n, func_data);
            n = n->next;     
        }
}

void map_slnode_data_seq(sl_node_t *const node, void (*func)(void *, void *), void *func_data)
{    
    sl_node_t *n = node;
    while (n != NULL) {
        func(n->data, func_data);
        n = n->next;
    }
}

void map_dlnode_data_seq(dl_node_t *const node, void (*func)(void *, void *), void *func_data, bool reverse)
{
    dl_node_t *n = node;
    if (reverse) 
        while (n != NULL) {
            func(n->data, func_data);
            n = n->prev;
        }

    else 
        while (n != NULL) {
            func(n->data, func_data);
            n = n->next;     
        }
}

uint32_t count_slnode_seq(sl_node_t *const node)
{
    uint32_t counter = 0;
    sl_node_t *n = node;

    while(n != NULL) {
        counter++;
        n = n->next;
    }

    return counter;    
}

uint32_t count_dlnode_seq(dl_node_t *const node, bool reverse)
{
    uint32_t counter = 0;
    dl_node_t *n = node;

    if (reverse) 
        while (n != NULL) {
            counter++;
            n = n->prev;
        }
    else
        while (n != NULL) {
            counter++;
            n = n->next;
        }

    return counter;
}

sl_node_t *get_index_slnode_seq(sl_node_t *const node, uint32_t index)
{
    sl_node_t *n = node;
    uint32_t counter = 0;
    
    while (n != NULL && counter <= index) {
        if (index == counter)
            return n->data;
        n = n->next;
        counter++;
    }
    
    return NULL;
}

dl_node_t *get_index_dlnode_seq(dl_node_t *const node, uint32_t index)
{
    dl_node_t *n = node;
    uint32_t counter = 0;

    while(n != NULL && counter <= index) {
        if (counter == index)
            return n->data;
        n = n->next;
        counter++;
    }

    return NULL;
}

sl_node_t *cut_slnode_range(sl_node_t *const node, uint32_t start, uint32_t end) 
{
    if (start > 0) start--;

    sl_node_t *first = get_index_slnode_seq(node, start);
    sl_node_t *last = get_index_slnode_seq(node, end);

    if (first == NULL || last == NULL) return NULL;

    sl_node_t *tmp = first->next;
    first->next = last->next;
    last->next = NULL;

    return first; 
}

dl_node_t *cut_dlnode_range(dl_node_t *const node, uint32_t start, uint32_t end)
{
    dl_node_t *first = get_index_dlnode_seq(node, start);
    dl_node_t *last = get_index_dlnode_seq(node, end);

    if (first == NULL || last == NULL) return NULL;

    first->prev->next = last->next;
    last->next->prev = first->prev;

    return first;
}


