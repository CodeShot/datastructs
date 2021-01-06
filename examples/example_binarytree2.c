#include "datastructs.h"
#include <stdio.h>
#include <time.h>

//srand(time(0));

int64_t randomInt()
{
    return rand() - (RAND_MAX / 2); 
}

/**
 * BINARY TREE EXAMPLES AND TESTS
 */ 
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

    printf("Made %ld random numbers in %f seconds\n", inserts, in_seconds);

    start = clock(); 
    for (int i = 0; i < inserts; i++)
        add_binarytree(tree, &values[i]);
    end = clock();

    in_seconds = (double)(end - start) / (double)CLOCKS_PER_SEC;

    printf("Made %ld inserts in %f seconds\n", inserts, in_seconds);
    
    start = clock();
    free_binarytree(tree);
    end = clock();

    in_seconds = (double)(end - start) / (double)CLOCKS_PER_SEC;

    printf("Made %ld inserts in %f seconds\n", inserts, in_seconds);
}
