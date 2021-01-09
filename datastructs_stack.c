#include "datastructs.h"
#include <stdlib.h>

/**
 * Stack - core
 */
stack_t *create_stack()
{
    return malloc(sizeof(stack_t));
}

void push_stack(stack_t *s, void *data)
{
    sl_node_t *n = create_slnode(data);
    n->next = s->first;
    s->first = n;
}

void pop_stack(stack_t *s, void *data)
{
    if (s->first == NULL) {
        data = NULL;
        return;
    }    
    data = s->first->data;
    sl_node_t *n = s->first;
    s->first = s->first->next;
    free(n); // Regular free() intended
}

void free_stack(stack_t *s)
{
    free_slnode_seq(s->first);
    free(s);
}

/**
 * Stack - derived
 */

uint32_t count_stack(stack_t *s) 
{
    if (s->first == NULL)
        return 0;

    return 1; //count_slnode_seq(s->first);
}

void map_stack(stack_t *s, void (*func)(sl_node_t *, void *), void *func_data)
{
    
}

/**
 * map_stack example
 */
/**
#include <stdio.h>
void printCall(sl_node_t *n, void *data)
{
    printf("%d, ", *(uint8_t *)n->data);
}

int main()
{
    stack_t *s = ccreate_stack();
    uint8_t arr[5] = {1, 3, 4, 6, 9};

    for(int i = 0; i < 5; i++)
  
    push_stack(s, &arr[i]);

    map_stack(s, &printCall);
    
    free_stack(s);
    exit(EXIT_SUCCESS);
}
*/
