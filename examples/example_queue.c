#include "datastructs.h"

#include <stdio.h>

int main()
{
    int arr[] = {1, 2, 3, 4, 5};

    printf("Adding: 1, 2, 3, 4, 5\n");

    struct queue *q = create_queue();
    
    for (int i = 0; i < 5; i++) {  
        add_queue(q, &arr[i]);
    }

    for (int i = 0; i < 5; i++) {
        int *a = (int *)pop_queue(q);
        printf("%d, ", *a);
    }
    
    printf("\n");

    free_queue(q);

    exit(EXIT_SUCCESS);
}


