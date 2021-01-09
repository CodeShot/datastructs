#include "datastructs.h"


/**
 * Binary tree
 */
binarytree_t *create_binarytree()
{
    binarytree_t *t = malloc(sizeof(binarytree_t));
    return t;
}

void *lowest_binarytree(binarytree_t *t)
{
    if (t->root == NULL)
        return NULL;

    dlp_node_t *previous = t->root;
    dlp_node_t *current = t->root->prev;

    while (current != NULL) {
        previous = current;
        current = current->prev;
    }
    
    return previous->data;
}

void *highest_binarytree(binarytree_t *t)
{
    if (t->root == NULL)
        return NULL;

    dlp_node_t *previous = t->root;
    dlp_node_t *current = t->root->next;;

    while (current != NULL) {
        previous = current;
        current = current->next;
    }
    
    return previous->data;
}

int8_t add_binarytree(binarytree_t *t, void *data)
{
    if (t->root == NULL) {
        t->root = create_dlpnode(data);
        return 1;
    }

    dlp_node_t *current = t->root;

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

dlp_node_t *find_binarytree(dlp_node_t *n, void *data)
{
    if (n == NULL) return NULL;
    if (n->data == data) return n;
    
    dlp_node_t *walk = find_binarytree(n->prev, data);

    if (walk != NULL) return walk;

    return find_binarytree(n->next, data);
}

int8_t del_binarytree(binarytree_t *t, void *data)
{
    dlp_node_t *found = find_binarytree(t->root, data);

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

void free_sub_binarytree(dlp_node_t *start)
{
    if (start == NULL) return;

    free_sub_binarytree(start->prev);
    free_sub_binarytree(start->next);
    
    free_dlpnode(start);
}

void free_binarytree(binarytree_t *t)
{
    if (t->root == NULL) return;
    free_sub_binarytree(t->root);
    if (t != NULL) free(t);
}
