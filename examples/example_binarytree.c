#include "datastructs.h"
#include <stdio.h>

int main() 
{
    struct binarytree *tree = create_binarytree();

    if (tree == NULL) {
        printf("No tree?!\n");
        exit(EXIT_FAILURE);
    }

    uint8_t values[] = {50, 20, 10, 90, 70};

    for (int i = 0; i < 5; i++)
        add_binarytree(tree, &values[i]);

//    printf("root: %d, left: %d, left: %d\n", tree->root->data, tree->root->prev->data, tree->root->prev->prev->data);

    printf("Root: %d\n", *((uint8_t *)tree->root->data));

    uint8_t a = 70;

    if (find_binarytree(tree->root, &a) != NULL)
        printf("Found one value correctly\n");

    a = 35;

    if (find_binarytree(tree->root, &a) == NULL)
        printf("Did not find value as supposed\n");


    free_binarytree(tree);

    exit(EXIT_SUCCESS);
}

