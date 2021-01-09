#include "datastructs.h"

tree_t *create_tree()
{
    return malloc(sizeof(tree_t));
}

void add_tree(tree_node_t *n, void *data)
{
    if (n->children == NULL)
        n->children = create_queue();

    add_queue(n->children, data);
}

void del_tree(tree_node_t *n)
{

}
