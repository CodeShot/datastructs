#include "datastructs.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * Set 
 */
set_t *create_set()
{
    return malloc(sizeof(set_t));
}

int8_t add_set(set_t *const s, void *const data)
{
    return add_binarytree(s->tree, data);
}

int8_t contains_set(set_t *const s, void *const data)
{
    dlp_node_t *n = find_binarytree(s->tree->root, data);

    if (n == NULL)
        return 0;
    else
        return 1;
}

int8_t del_set(set_t *const s, void *const data)
{
    return del_binarytree(s->tree, data);
}

void free_set(set_t *s)
{
    free_binarytree(s->tree);
    free(s);
}
