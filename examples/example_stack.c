#include "datastructs.h"

#include <stdio.h>

int main()
{
    int arr[] = {1, 2, 3, 4, 5};

    printf("Adding: 1, 2, 3, 4, 5\n");

    struct stack *s = create_stack();
    
    for (int i = 0; i < 5; i++) {  
        add_stack(s, &arr[i]);
    }

    for (int i = 0; i < 5; i++) {
        int *a = pop_stack(s);

        printf("%d, ", *a);
    }
    
    printf("\n");

    free_stack(s);

    exit(EXIT_SUCCESS);
}


