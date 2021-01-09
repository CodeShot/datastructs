#include "datastructs.h"

#include <stdio.h>

int main()
{
    int arr[] = {1, 2, 3, 4, 5};

    printf("Adding: 1, 2, 3, 4, 5\n");

    struct queue *q = create_queue();
    struct stack *s = create_stack();
    struct deque *dq = create_deque();

    for (int i = 0; i < 5; i++) {  
        add_queue(q, &arr[i]);
        add_stack(s, &arr[i]);
        add_first_deque(dq, &arr[i]);
    }

    printf("Queue\tStack\tDeque (last)\n");
    
    for (int i = 0; i < 5; i++) {
        int *qv = pop_queue(q);
        int *sv = pop_stack(s);
        int *dv = pop_last_deque(dq);
        
        printf("%d\t%d\t%d\n", *qv, *sv, *dv);
    } 
    printf("\n");

    free_queue(q);

    exit(EXIT_SUCCESS);
}


