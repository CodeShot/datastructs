/**
 * @file datastructs.h
 *
 * Datastructs uses different nodetypes to implement datastructures.
 *
 * - sl_node_t *for stack and queue*
 * - dl_node_t *for deque*
 * - dlp_node_t *for binarytree*
 * - tree_node_t *for tree*
 * 
 * The primary intentended use case of this library would be without 
 * interacting with node objects.
 *
 * At this level only relational aspects such as a datastructure being 
 * sequential or hierarchical are fully implemented.
 *
 * All datastructures have been implemented and tested with explicit pointer
 * types instead of void pointer. 
 * Datastructures in pipeline:
 *  - stack (stable implemented)
 *  - queue (stable implemented)
 *  - deque (stable/slow not the nicest implementation, no priority)
 *  - binarytree (not functional with void pointers)
 *  - set (depends on binarytree stable when binarytree is stable)
 *  - bag (NOT IMPLEMENTED YET)
 *  - tree (NOT IMPLEMENTED YET)
 *
 *  Roadmap:
 *  - **general manner of determining likeness of data based on pointer size**
 *  - **considering: add overall support for variadic arguments**
 *  - **naming conventions must be resolved**
 *  - **consider how to implement datastructure properties**
 *  - **implement push&pop-stack queue**
 */

#ifndef _DATASTRUCTS_H
#define _DATASTRUCTS_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

/** Single linked node */
struct sl_node {
    void *data;           /**< pointer to object stored by node */ 
    struct sl_node *next; /**< pointer to sequential neighbor */
};

/** Double linked node */
struct dl_node {
    void *data;             /**< pointer to object stored by node */ 
    struct dl_node *prev;   /**< pointer to sequential neighbor */
    struct dl_node *next;   /**< pointer to sequential neighbor */
};

/** Double linked node with parent */
struct dlp_node {
    void *data;                 /**< pointer to object stored by node */ 
    struct dlp_node *parent;    /**< pointer to hierarchical parent */
    struct dlp_node *prev;      /**< pointer to hierarchical child */
    struct dlp_node *next;      /**< pointer to hierarchical child */
};

/** Node with parent and a queue of children (todo: make hashmap ;S) */
struct tree_node {
    void *data;/**< pointer to object stored by node */ 

    struct tree_node *parent;   /**< pointer to hierarchical parent */
    struct queue *children;     /**< pointer to queue of hierarchical children */
};

/** Sequential single linked (repeater) */
struct queue {
    struct sl_node *first;  /**< pointer to first node in queue */
    struct sl_node *last;   /**< pointer to last node in queue */
};

/** Sequential single linked (reverser) */
struct stack {
    struct sl_node *first; /**< pointer to first item in stack */
};

/** Sequential double linked (repeater & reverser) */
struct deque {
    struct dl_node *first;  /**< pointer to first node in deque */
    struct dl_node *last;   /**< pointer to last node in deque */
    uint32_t count;         /**< number of items in deque */
};

/** Binary tree (sorter) */
struct binarytree {
    struct dlp_node *root;  /**< pointer to root node of binarytree */
};

/** Sequential sorter */
struct set {
    struct binarytree *tree;    /**< pointer to binarytree */
};

/** Sequential sorter and counter */
struct bag {
    struct binarytree *tree;    /**< pointer to binarytree */
};

/** Arbitrary tree for hierarchical relational storage */
struct tree {
    struct tree_node *root;     /**< pointer to root node of binarytree */
};

/* Nodetypes */
typedef struct sl_node  sl_node_t;
typedef struct dl_node  dl_node_t;
typedef struct dlp_node dlp_node_t;
typedef struct tree_node tree_node_t;

/* Datastructures */
typedef struct stack    stack_t;
typedef struct queue    queue_t;
typedef struct deque    deque_t;
typedef struct tree     tree_t;
typedef struct set      set_t;
typedef struct bag      bag_t;
typedef struct binarytree binarytree_t;

/**
 * @defgroup Node Node functions
 * @{
 */

/**  
 * Create a sl_node instance.
 * @param[in] data pointer to object
 * @return pointer to newly created sl_node
 */
sl_node_t *create_slnode(void *const data);

/**
 * Helper to fully free sl_node instance and its data pointer.
 * @param[in] n pointer to sl_node instance
 */
void free_slnode(sl_node_t *n);

/**  
 * Create a dl_node instance.
 * @param[in] data pointer to object
 * @return pointer to newly created dl_node
 */
dl_node_t *create_dlnode(void *const data);

/**
 * Helper to fully free dl_node instance and its data pointer.
 * @param[in] n pointer to dl_node instance
 */
void free_dlnode(dl_node_t *n);

/**  
 * Create a dlp_node instance.
 * @param[in] data pointer to object
 * @return pointer to newly created dlp_node
 */
dlp_node_t *create_dlpnode(void *const data);

/**
 * Helper to fully free dlp_node instance and its data pointer.
 * @param[in] n pointer to dlp_node instance
 */
void free_dlpnode(dlp_node_t *n);

/**  
 * Create a tree_node instance.
 * @param[in] data pointer to object
 * @return pointer to newly created tree_node
 */
tree_node_t *create_treenode(void *const data);

/**
 * Helper to fully free tree_node instance and its data pointer.
 * @param[in] n pointer to tree_node instance
 */
void free_treenode(tree_node_t *n);

/**
 * Helper for clearing every sequentially linked sl_node.
 * @param[in] n pointer to beginning of sl_node sequence
 */
void free_slnode_seq(sl_node_t *n); // Helper for clearing

/**
 * Helper for clearing every sequentially linked dl_node.
 * @param[n] n pointer to beginning of dl_node sequence
 */
void free_dlnode_seq(dl_node_t *n); // sequence of nodes

/**
 * Map a function to interact with each sl_node_t in a sequence of nodes with 
 * *node* pointer passed being the first. The function interacting will get a 
 * sl_node_t pointer as first parameter and func_data as second.
 * @param[in] node pointer to starting node
 * @param[in] func function pointer to user defined function
 * @param[out] func_data pointer to data for user defined function, NULL allowed
 */
void map_slnode_seq(sl_node_t *const node, void (*func)(sl_node_t *, void *), void *func_data);

/**
 * Map a function to interact with each dl_node_t in a sequence of nodes with 
 * *node* pointer passed being the first. The function interacting will get a 
 * dl_node_t pointer as first parameter and func_data as second.
 * @param[in] node pointer to starting node
 * @param[in] func function pointer to user defined function
 * @param[out] func_data pointer to data for user defined function, NULL allowed
 * @param[in] reverese boolean value, if left true/1 it movement is reversed
 */
void map_dlnode_seq(dl_node_t *const node, void (*func)(dl_node_t *, void *), void *func_data, bool reverse);

/**
 * Map a function to interact with each data pointer in a sequence of nodes with 
 * *node* pointer passed being the first. The function interacting will get a 
 * data pointer as first parameter and func_data as second.
 * @param[in] node pointer to starting node
 * @param[in] func function pointer to user defined function
 * @param[out] func_data pointer to data for user defined function, NULL allowed
 */
void map_slnode_data_seq(sl_node_t *const node, void (*func)(void *, void *), void *func_data);

/**
 * Map a function to interact with each data pointer in a sequence of nodes with 
 * *node* pointer passed being the first. The function interacting will get a 
 * data pointer as first parameter and func_data as second.
 * @param[in] node pointer to starting node
 * @param[in] func function pointer to user defined function
 * @param[out] func_data pointer to data for user defined function, NULL allowed
 * @param[in] reverese boolean value, if left true/1 it movement is reversed
 */
void map_dlnode_data_seq(dl_node_t *const node, void (*func)(void *, void *), void *func_data, bool reverse);

/**
 * Count the number of nodes a sl_node_t sequence us from and inlcluding *node*.
 * @param node pointer to start of count
 * @return number of nodes
 */
uint32_t count_slnode_seq(sl_node_t *const node);

/**
 * Count the number of nodes a dl_node_t sequence us from and inlcluding *node*.
 * @param node pointer to start of count
 * @param[in] reverese boolean value, if left true/1 it movement is reversed
 * @return nuber of nodes
 */
uint32_t count_dlnode_seq(dl_node_t *const node, bool reverse);

/**
 * @}
 */

/**
 * @defgroup Queue Queue functions
 * @{
 */

/**
 * Create a queue instance.
 * @return pointer to newly created queue 
 */
queue_t *create_queue();

/**
 * Free queue instance and all its nodes
 * @param[in] q pointer to queue instance
 */
void free_queue(queue_t *q);

/**
 * Add a node to queue.
 * @param[out] q pointer to queue
 * @param{in] data pointer to node data
 */
void add_queue(queue_t *const q, void *const data);

/**
 * Pop a node from the queue (FIFO).
 * @param[out] q pointer to queue
 * @return data pointer stored by the node
 */
void *pop_queue(queue_t *const q);

/**
 * @}
 */

/**
 * @defgroup Stack Stack functions
 * @{
 */

/**
 * Create a stack instance.
 * @return pointer to newly created stack 
 */
stack_t *create_stack();

/**
 * Free queue instance and all its nodes
 * @param[in] q pointer to queue instance
 */
void free_stack(stack_t *s);

/**
 * Add (push) a node to the stack.
 * @param[out] s pointer to stack instance
 * @param[in] data pointer to node data
 */
void add_stack(stack_t *const s, void *const data);

/**
 * Pop a node from the stack (LIFO).
 * @param[out] s pointer to stack instance
 * @return data pointer stored by the node
 */
void *pop_stack(stack_t *const s);

void map_stack(stack_t *const s, void (*func)(sl_node_t *, void *), void *func_data); 
/**
 * @}
 */

/**
 * @defgroup Deque Deque functions
 * @{
 */

/**
 * Create a deque instance.
 * @return pointer to newly created deque 
 */
deque_t *create_deque();

/**
 * Free queue instance and all its nodes
 * @param[in] q pointer to queue instance
 */
void free_deque(deque_t *dq);

/**
 * Add a node to beginning of deque.
 * @param[out] dq pointer to deque instance
 * @param[in] data pointer to node data
 */
void add_first_deque(deque_t *const dq, void *const data);

/**
 * Add a node to end of deque.
 * @param[out] dq pointer to deque instance
 * @param[in] data pointer to node data
 */
void add_last_deque(deque_t *const dq, void *const data);

/**
 * Pop a node from the beginning of the deque.
 * @param[out] s pointer to deque instance
 * @return data pointer stored by the node
 */
void *pop_first_deque(deque_t *const dq);

/**
 * Pop a node from the end of the deque.
 * @param[out] s pointer to deque instance
 * @return data pointer stored by the node
 */
void *pop_last_deque(deque_t *const dq);
/**
 * @}
 */

/**
 * @defgroup Binarytree Binarytree functions
 * @{
 */

/**
 * Create a binarytree instance.
 * @return pointer to newly created binarytree
 */
binarytree_t *create_binarytree();

/**
 * Free binarytree instance and all its dlp_node references.
 * @param[in] t pointer to queue instance
 */
void free_binarytree(binarytree_t *t);

/**
 * Helper to free nodes of a binarytree recursively below a certain node.
 * @param[in] n pointer to node to free recursively
 */
void free_sub_binarytree(dlp_node_t *n);

/**
 * Add node to a binarytree.
 * @param[out] t pointer to binarytree instance
 * @param[in] data pointer to node data
 * @return result (0 if already in binarytree, 1 if added successfully)
 */
int8_t add_binarytree(binarytree_t *const t, void *const data);

/**
 * Delete only node specified by data and reconstruct binarytree accordingly.
 * @param[in] t pointer to binarytree instance
 * @param[in] data pointer to data that will qualify deletion 
 */
int8_t del_binarytree(binarytree_t *const t, void *const data);

/**
 * Find node in a binarytree.
 * @param[out] n pointer to starting node 
 * @param[in] data pointer to node data
 * @return result (-1 if already in binarytree, 1 if added successfully)
 */
dlp_node_t *find_binarytree(dlp_node_t *const n, void *const data);

/**
 * Get node with lowest value on evaluation (WARN: bugged).
 * @param[in] t pointer to binarytree instance
 * @return pointer to node data or NULL if binarytree is empty
 */
void *lowest_binarytree(binarytree_t *const t);

/**
 * Get node with highest value on evaluation (WARN: bugged).
 * @param[in] t pointer to binarytree instance
 * @return pointer to node data or NULL if binarytree is empty
 */
void *highest_binarytree(binarytree_t *const t);
/**
 * @}
 */

/**
 * @defgroup Set Set functions
 * @{
 */

/**
 * Create a set instance.
 * @return pointer to newly created set 
 */
set_t *create_set();

/**
 * Free set instance and all its associated node references.
 * @param[in] s pointer to set instance
 */
void free_set(set_t *s);

/**
 * Add node to a set.
 * @param[out] s pointer to set
 * @param[in] data pointer to node data
 * @return result (0 if already in set, 1 if added successfully)
 */
int8_t add_set(set_t *const s, void *const data);

/**
 * Find node in a set.
 * @param[out] s pointer to set
 * @param[in] data pointer to node data
 * @return result (-1 if already in set, 1 if added successfully)
 */
int8_t find_set(set_t *const s, void *const data);

/**
 * Delete node in a set.
 * @param[out] s pointer to set instance
 * @param[in] data pointer to data to search for
 * @return result (-1 if not found, 1 if deleted successfully) 
 */
int8_t del_set(set_t *const s, void *const data);
/**
 * @}
 */

/**
 * @defgroup Tree Tree functions
 * @{
 */

/**
 * Create a tree instance.
 * @return pointer to newly created tree 
 */
struct tree *create_tree();

/**
 * Free tree instance and all its tree_node references.
 * @param[in] t pointer to tree instance
 */
void free_tree(tree_t *t);

/**
 * Add node to a set.
 * @param[out] n pointer to tree_node instance  
 * @param[in] data pointer to node data
 * @return result (0 if already in set, 1 if added successfully)
 */
int8_t add_child_treenode(tree_node_t *n, void *data);
int8_t del_child_treenode(tree_node_t *n, void *data);

/**
 * Find node in a tree.
 * @param[out] t pointer to tree 
 * @param[in] data pointer to node data
 * @return result (-1 if already in tree, 1 if added successfully)
 */
tree_node_t *find_tree(tree_t *t, void *data);
/**
 * @}
 */

#endif
