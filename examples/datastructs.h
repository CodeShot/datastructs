#ifndef _DATASTRUCTS_H
#define _DATASTRUCTS_H

/*
 * All datastructures are to be used with only values/data.
 * Nodes will thus be containers handled solely by the datastructures.
 * Data is passad as void pointers to and from datastructures.
 */

#include <stdlib.h>
#include <stdint.h>

// Nodes
struct sl_node {
    void *data;
    struct sl_node *next;
};

struct dl_node {
    void *data;
    struct dl_node *prev;
    struct dl_node *next;
};

struct dlp_node {
    void *data;
    struct dlp_node *parent;
    struct dlp_node *prev;
    struct dlp_node *next;
};

// Sequential single linked (repeater)
struct queue {
    struct sl_node *first;
    struct sl_node *last;
};

// Sequential single linked (reverser)
struct stack {
    struct sl_node *first;
};

// Sequential double linked (repeater & reverser)
struct deque {
    struct dl_node *first;
    struct dl_node *last;
    uint32_t count;
};

// Binary tree (sorter)
struct binarytree {
    struct dlp_node *root;
};

// Sequential sorter
struct set {
    struct binarytree *tree;
};

//Counter
struct bag {
    struct binarytree *tree;
};


// Nodes used in queue, dequeu, binarytree
struct sl_node *create_slnode(void *data);
void free_slnode(struct sl_node *n);


struct dl_node *create_dlnode(void *data);
void free_dlnode(struct dl_node *n);

struct dlp_node *create_dlpnode(void *data);
void free_dlpnode(struct dlp_node *n);

void free_slnode_seq(struct sl_node *n); // Helper for clearing
void free_dlnode_seq(struct dl_node *n); // sequence of nodes

// Queue used for FIFO access
struct queue *create_queue();
void free_queue(struct queue *q);

void add_queue(struct queue *q, void *data);
void *pop_queue(struct queue *q);

// Stack used for LIFO access
struct stack *create_stack();
void free_stack(struct stack *s);

void add_stack(struct stack *s, void *data);
void *pop_stack(struct stack *s);

// Deque for LIFO and FIFO access
struct deque *create_deque();
void free_deque(struct deque *dq);

void add_first_deque(struct deque *dq, void *data);
void add_last_deque(struct deque *dq, void *data);
void *pop_first_deque(struct deque *dq);
void *pop_last_deque(struct deque *dq);

// Sorted binarytree used for set 
struct binarytree *create_binarytree();
int8_t add_binarytree(struct binarytree *tree, void *data);

struct dlp_node *find_binarytree(struct dlp_node *n, void *data);
void *lowest_binarytree(struct binarytree *tree);
void *highest_binarytree(struct binarytree *tree);

void free_sub_binarytree(struct dlp_node *n);
void free_binarytree(struct binarytree *tree);

// Set
struct set *create_set();
int8_t add_set(struct set *s, void *data);
int8_t find_set(struct set *s, void *data);
int8_t del_set(struct set *s, void *data);
void free_set(struct set *s); 

#endif
