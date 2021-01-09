#include "datastructs.h"
#include <stdio.h>
#include <string.h>

void print_node(dl_node_t *n, void *fdata)
{
    printf("%c", *(char*)n->data);
}

void print_data(void *ndata, void *fdata)
{
    printf("%c", *(char *)ndata);
}

struct parse_data {
    stack_t *open;
    queue_t *order;
    queue_t *tmp;
};

typedef struct parse_data parse_data_t;

void handle_nested_parent(void *ndata, void *fdata)
{
    parse_data_t *pd = (parse_data_t *)fdata;

    if (pd->tmp == NULL)
        pd->tmp = create_queue();

    if (*(char *)ndata == '(') {
        add_stack(pd->open, pd->tmp);
        pd->tmp = NULL;
    }
    else if (*(char *)ndata == ')') {
        add_queue(pd->order, pd->tmp);
        pd->tmp = pop_stack(pd->open);
    }
    else {
        add_queue(pd->tmp, ndata);
    }
}

void print_queue(void *ndata, void *fdata)
{
    queue_t *q = (queue_t *)ndata;
    map_slnode_data_seq(q->first, print_data, fdata);
    printf(" ");
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Don't be so stiff provide a argument please\n");
        exit(EXIT_SUCCESS);
    }

    char *str = argv[1];
    int len = strlen(str);
    deque_t *dq = create_deque();

    for (int i = 0; i < len; i++)
        add_last_deque(dq, (str + i));

    printf("Print '%s' reversed: ", argv[1]);
    map_deque(dq, print_node, NULL, 1);
    printf("\n");

    parse_data_t *pd = malloc(sizeof(*pd));
    pd->open = create_stack();
    pd->order = create_queue();

    map_dlnode_data_seq(dq->first, handle_nested_parent, pd, 0);
    map_slnode_data_seq(pd->order->first, print_queue, NULL);
    printf("\n");

    free_stack(pd->open);
    free_queue(pd->order);
    free_queue(pd->tmp);

    free_deque(dq);
    exit(EXIT_SUCCESS);
}

