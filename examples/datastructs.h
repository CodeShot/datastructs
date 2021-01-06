/**
 * @file datastructs.h
 *
 * Datastructs uses different nodetypes to implement datastructures.
 *
 * - sl_node *for stack and queue*
 * - dl_node *for deque*
 * - dlp_node *for binarytree*
 * - tree_node *for tree*
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
 *  - **general manner of determininglikeness of data based on pointer size**
 *  - **add overall support for variadic arguments**
 *  - **consider naming conventions early on**
 *  - **consider macros for setting overall behaviors, as choice of implementation**
 *  - **implement push&pop-stack queue for to investigate macros to alternate implementations**
 */

#ifndef _DATASTRUCTS_H
#define _DATASTRUCTS_H

#include <stdint.h>
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

/**
 * @defgroup Node Node functions
 * @{
 */

/**  
 * Create a sl_node instance.
 * @param[in] data pointer to object
 * @return pointer to newly created sl_node
 */
struct sl_node *create_slnode(void *data);

/**
 * Helper to fully free sl_node instance and its data pointer.
 * @param[in] n pointer to sl_node instance
 */
void free_slnode(struct sl_node *n);

/**  
 * Create a dl_node instance.
 * @param[in] data pointer to object
 * @return pointer to newly created dl_node
 */
struct dl_node *create_dlnode(void *data);

/**
 * Helper to fully free dl_node instance and its data pointer.
 * @param[in] n pointer to dl_node instance
 */
void free_dlnode(struct dl_node *n);

/**  
 * Create a dlp_node instance.
 * @param[in] data pointer to object
 * @return pointer to newly created dlp_node
 */
struct dlp_node *create_dlpnode(void *data);

/**
 * Helper to fully free dlp_node instance and its data pointer.
 * @param[in] n pointer to dlp_node instance
 */
void free_dlpnode(struct dlp_node *n);

/**  
 * Create a tree_node instance.
 * @param[in] data pointer to object
 * @return pointer to newly created tree_node
 */
struct tree_node *create_treenode(void *data);

/**
 * Helper to fully free tree_node instance and its data pointer.
 * @param[in] n pointer to tree_node instance
 */
void free_treenode(struct tree_node *n);

/**
 * Helper for clearing every sequentially linked sl_node.
 * @param[in] n pointer to beginning of sl_node sequence
 */
void free_slnode_seq(struct sl_node *n); // Helper for clearing

/**
 * Helper for clearing every sequentially linked dl_node.
 * @param[n] n pointer to beginning of dl_node sequence
 */
void free_dlnode_seq(struct dl_node *n); // sequence of nodes
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
struct queue *create_queue();

/**
 * Free queue instance and all its nodes
 * @param[in] q pointer to queue instance
 */
void free_queue(struct queue *q);

/**
 * Add a node to queue.
 * @param[out] q pointer to queue
 * @param{in] data pointer to node data
 */
void add_queue(struct queue *q, void *data);

/**
 * Pop a node from the queue (FIFO).
 * @param[out] q pointer to queue
 * @return data pointer stored by the node
 */
void *pop_queue(struct queue *q);

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

struct stack *create_stack();
/**
 * Free queue instance and all its nodes
 * @param[in] q pointer to queue instance
 */
void free_stack(struct stack *s);

/**
 * Add (push) a node to the stack.
 * @param[out] s pointer to stack instance
 * @param[in] data pointer to node data
 */
void add_stack(struct stack *s, void *data);

/**
 * Pop a node from the stack (LIFO).
 * @param[out] s pointer to stack instance
 * @return data pointer stored by the node
 */
void *pop_stack(struct stack *s);
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
struct deque *create_deque();

/**
 * Free queue instance and all its nodes
 * @param[in] q pointer to queue instance
 */
void free_deque(struct deque *dq);

/**
 * Add a node to beginning of deque.
 * @param[out] dq pointer to deque instance
 * @param[in] data pointer to node data
 */
void add_first_deque(struct deque *dq, void *data);

/**
 * Add a node to end of deque.
 * @param[out] dq pointer to deque instance
 * @param[in] data pointer to node data
 */
void add_last_deque(struct deque *dq, void *data);

/**
 * Pop a node from the beginning of the deque.
 * @param[out] s pointer to deque instance
 * @return data pointer stored by the node
 */
void *pop_first_deque(struct deque *dq);

/**
 * Pop a node from the end of the deque.
 * @param[out] s pointer to deque instance
 * @return data pointer stored by the node
 */
void *pop_last_deque(struct deque *dq);
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
struct binarytree *create_binarytree();

/**
 * Free binarytree instance and all its dlp_node references.
 * @param[in] t pointer to queue instance
 */
void free_binarytree(struct binarytree *t);

/**
 * Helper to free nodes of a binarytree recursively below a certain node.
 * @param[in] n pointer to node to free recursively
 */
void free_sub_binarytree(struct dlp_node *n);

/**
 * Add node to a binarytree.
 * @param[out] t pointer to binarytree instance
 * @param[in] data pointer to node data
 * @return result (0 if already in binarytree, 1 if added successfully)
 */
int8_t add_binarytree(struct binarytree *t, void *data);

/**
 * Find node in a binarytree.
 * @param[out] n pointer to starting node 
 * @param[in] data pointer to node data
 * @return result (-1 if already in binarytree, 1 if added successfully)
 */
struct dlp_node *find_binarytree(struct dlp_node *n, void *data);

/**
 * Get node with lowest value on evaluation (WARN: bugged).
 * @param[in] t pointer to binarytree instance
 * @return pointer to node data or NULL if binarytree is empty
 */
void *lowest_binarytree(struct binarytree *t);

/**
 * Get node with highest value on evaluation (WARN: bugged).
 * @param[in] t pointer to binarytree instance
 * @return pointer to node data or NULL if binarytree is empty
 */
void *highest_binarytree(struct binarytree *t);
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
struct set *create_set();

/**
 * Free set instance and all its associated node references.
 * @param[in] s pointer to set instance
 */
void free_set(struct set *s);

/**
 * Add node to a set.
 * @param[out] s pointer to set
 * @param[in] data pointer to node data
 * @return result (0 if already in set, 1 if added successfully)
 */
int8_t add_set(struct set *s, void *data);

/**
 * Find node in a set.
 * @param[out] s pointer to set
 * @param[in] data pointer to node data
 * @return result (-1 if already in set, 1 if added successfully)
 */
int8_t find_set(struct set *s, void *data);

/**
 * Delete node in a set.
 * @param[out] s pointer to set instance
 * @param[in] data pointer to data to search for
 * @return result (-1 if not found, 1 if deleted successfully) 
 */
int8_t del_set(struct set *s, void *data);
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
void free_tree(struct tree *t);

/**
 * Add node to a set.
 * @param[out] n pointer to tree_node instance  
 * @param[in] data pointer to node data
 * @return result (0 if already in set, 1 if added successfully)
 */
int8_t add_child_treenode(struct tree_node *n, void *data);
int8_t del_child_treenode(struct tree_node *n, void *data);

/**
 * Find node in a tree.
 * @param[out] t pointer to tree 
 * @param[in] data pointer to node data
 * @return result (-1 if already in tree, 1 if added successfully)
 */
struct tree_node *find_tree(struct tree *t, void *data);
/**
 * @}
 */
#endif
