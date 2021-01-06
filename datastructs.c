#include "datastructs.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Node types, create and free
 */
struct sl_node *create_slnode(void *data) 
{
    struct sl_node *n = malloc(sizeof(*n));
    n->data = data;
    return n;
}

struct dl_node *create_dlnode(void *data) 
{
    struct dl_node *n = malloc(sizeof(*n));
    n->data = data;
    return n;
}

struct dlp_node *create_dlpnode(void *data) 
{
    struct dlp_node *n = malloc(sizeof(*n));
    n->data = data;
    return n;
}

void free_slnode(struct sl_node *n)
{
    free(n->data);
    free(n);
}

void free_dlnode(struct dl_node *n)
{
    free(n->data);
    free(n);
}

void free_dlpnode(struct dlp_node *n)
{
    free(n->data);
    free(n);
}

void free_slnode_seq(struct sl_node *n)
{
    struct sl_node *tmp;

    while (n != NULL) {
        tmp = n->next;
        free_slnode(n);
        n = tmp;
    }
}

void free_dlnode_seq(struct dl_node *n)
{
    struct dl_node *tmp;

    while (n != NULL) {
        tmp = n->next;
        free_dlnode(n);
        n = tmp;
    }
}

/**
 * Stack
 */
struct stack *create_stack()
{
    return malloc(sizeof(struct stack));
}

void add_stack(struct stack *s, void *data)
{
    struct sl_node *n = create_slnode(data);
    n->next = s->first;
    s->first = n;
}

void *pop_stack(struct stack *s)
{
    if (s->first == NULL) return NULL;
    struct sl_node *n = s->first;
    s->first = s->first->next;

    void *data = n->data;
    free(n); // Regular free() intended
    return data;
}

void free_stack(struct stack *s)
{
    free_slnode_seq(s->first);
    free(s);
}


/**
 * Queue
 */
struct queue *create_queue()
{
    return malloc(sizeof(struct queue));
}

void add_queue(struct queue *q, void *data)
{
    if (q->last == NULL)
        q->last = q->first = create_slnode(data);
    else {
        q->last->next = create_slnode(data);
        q->last = q->last->next;
    }
}

void *pop_queue(struct queue *q)
{
    if (q->first == NULL) return NULL;

    struct sl_node *tmp = q->first;
    q->first = q->first->next;
    void *data = tmp->data;
    
    free(tmp); // Regular free() as we return the data pointer

    return data;
}

void free_queue(struct queue *q)
{
    free_slnode_seq(q->first);
    free(q);
}


/**
 * Deque
 */
struct deque *create_deque()
{
    struct deque *dq = malloc(sizeof(struct deque));
    dq->count = 0;
    return dq;
}

void add_first_deque(struct deque *dq, void *data)
{
    struct dl_node *n = create_dlnode(data);
    
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

void add_last_deque(struct deque *dq, void *data)
{
    struct dl_node *n = create_dlnode(data);

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

void *pop_first_deque(struct deque *dq)
{
    if (dq->first == NULL)
        return NULL;

    struct dl_node *n = dq->first;
    dq->first = dq->first->next;
    dq->count--;
    void *data = n->data;
    free(n);
    return data;
}

void *pop_last_deque(struct deque *dq)
{
    if (dq->last == NULL)
        return NULL;

    struct dl_node *n = dq->last;
    dq->last = dq->last->prev;

    dq->count--;
    void *data = n->data;
    free(n);
    return data;
}

void *contains_deque(struct deque *dq)
{
    struct dl_node *n = dq->last;
    dq->last = dq->last->prev;
    return n->data;
}

void free_deque(struct deque *dq)
{
    free_dlnode_seq(dq->first);
    free(dq);
}


/**
 * Binary tree
 */
struct binarytree *create_binarytree()
{
    struct binarytree *t = malloc(sizeof(struct binarytree));
    return t;
}

void *lowest_binarytree(struct binarytree *t)
{
    if (t->root == NULL)
        return NULL;

    struct dlp_node *previous = t->root;
    struct dlp_node *current = t->root->prev;

    while (current != NULL) {
        previous = current;
        current = current->prev;
    }
    
    return previous->data;
}

void *highest_binarytree(struct binarytree *t)
{
    if (t->root == NULL)
        return NULL;

    struct dlp_node *previous = t->root;
    struct dlp_node *current = t->root->next;;

    while (current != NULL) {
        previous = current;
        current = current->next;
    }
    
    return previous->data;
}

int8_t add_binarytree(struct binarytree *t, void *data)
{
    if (t->root == NULL) {
        t->root = create_dlpnode(data);
        return 1;
    }

    struct dlp_node *current = t->root;

    while (1) {
        if (current->data == data)
            return 0;
        else if (current->data > data) {
            if (current->prev == NULL) {
                current->prev = create_dlpnode(data);
                current->prev->parent = current;
                return 1;
            }
            else current = current->prev;
        }
        else {
            if (current->next == NULL) {
                current->next = create_dlpnode(data);
                current->next->parent = current;
                return 1;
            }
            else current = current->next;
        }
    }
}

struct dlp_node *find_binarytree(struct dlp_node *n, void *data)
{
    if (n == NULL) return NULL;
    if (n->data == data) return n;
    
    struct dlp_node *walk = find_binarytree(n->prev, data);

    if (walk != NULL) return walk;

    return find_binarytree(n->next, data);
}

int8_t del_binarytree(struct binarytree *t, void *data)
{
    struct dlp_node *found = find_binarytree(t->root, data);

    if (found == NULL) return -1;
   
    // move up right side of this node to keep tree left-heavy
    while (found->next != NULL) {
        found->next->parent = found->parent;
        found->prev->parent = found->next;
    }

    // our while loop did no modifications so we move up left node
    if (found->data == data) {
        found->prev->parent = found->parent;
        found = found->prev;
    }

    return 1;    
}

void free_sub_binarytree(struct dlp_node *start)
{
    if (start == NULL) return;

    free_sub_binarytree(start->prev);
    free_sub_binarytree(start->next);
    
    free_dlpnode(start);
}

void free_binarytree(struct binarytree *t)
{
    if (t->root == NULL) return;
    free_sub_binarytree(t->root);
    if (t != NULL) free(t);
}


/**
 * Set 
 */
struct set *create_set()
{
    return malloc(sizeof(struct set));
}

int8_t add_set(struct set *s, void *data)
{
    return add_binarytree(s->tree, data);
}

int8_t contains_set(struct set *s, void *data)
{
    struct dlp_node *n = find_binarytree(s->tree->root, data);

    if (n == NULL)
        return 0;
    else
        return 1;
}

int8_t del_set(struct set *s, void *data)
{
    return del_binarytree(s->tree, data);
}

void free_set(struct set *s)
{
    free_binarytree(s->tree);
    free(s);
}

// Needed for binary tree and set examples

/*
#include <stdio.h>
#include <time.h>

//srand(time(0));

int64_t randomInt()
{
    return rand() - (RAND_MAX / 2); 
}

*/

/**
 * BINARY TREE EXAMPLES AND TESTS
 */

/* 
int main()
{
    uint64_t inserts = 1000000;

    struct binarytree *tree = create_binarytree();
    int64_t *values = malloc(sizeof(*values) * inserts);

    if (values == NULL)
        printf("Test value allocation failed");
    
    clock_t start, end;
    double in_seconds;

    start = clock();
    for (int i = 0; i < inserts; i++)
        values[i] = randomInt();
    end = clock();

    in_seconds = (double)(end - start) / (double)CLOCKS_PER_SEC;

    printf("Made %d random numbers in %f seconds\n", inserts, in_seconds);

    start = clock(); 
    for (int i = 0; i < inserts; i++)
        add_binarytree(tree, values[i]);
    end = clock();

    in_seconds = (double)(end - start) / (double)CLOCKS_PER_SEC;

    printf("Made %d inserts in %f seconds\n", inserts, in_seconds);
    
    start = clock();
    free_binarytree(tree->root);
    end = clock();

    in_seconds = (double)(end - start) / (double)CLOCKS_PER_SEC;

    printf("Made %d inserts in %f seconds\n", inserts, in_seconds);
}

*/
