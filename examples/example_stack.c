#include "datastructs.h"

#include <stdio.h>

void print_node(sl_node_t *n, void *fdata)
{
    printf("%d, ", *(int*)n->data);
}


void print_data(void *ndata, void *fdata)
{
    printf("%d, ", *(int*)ndata);
}


int main()
{
    int arr[] = {1, 2, 3, 4, 5};

    printf("Adding: 1, 2, 3, 4, 5\n");

    struct stack *s = create_stack();
    
    for (int i = 0; i < 5; i++) {  
        add_stack(s, &arr[i]);
    }

    map_stack(s, print_node, NULL);
    printf("\n");
    map_slnode_data_seq(s->first, print_data, NULL);
    printf("\n");

    for (int i = 0; i < 5; i++) {
        int *a = pop_stack(s);

        printf("%d, ", *a);
    }
    
    printf("\n");

    free_stack(s);

    exit(EXIT_SUCCESS);
}


