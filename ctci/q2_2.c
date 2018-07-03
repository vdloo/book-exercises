#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Return the k-th element of a linked list */

/*
  $ gcc q2_2.c && ./a.outThe linked list looks like:
  9
  8
  7
  6
  5
  4
  3
  2
  1
  0
  The 0th to last element has value 0
  The third to last element has value 3
  The eight to last element has value 8
*/


typedef struct node_struct {
    int value;
    struct node_struct *next;
} node;

node *create_node(int value, node *next) {
    node * new_node = NULL;
    new_node = malloc(sizeof(node));
    if (new_node == NULL) {
        fprintf(
            stderr, "Failed to allocate memory for "
                    "new node in linked list\n"
        );
        exit(1);
    }
    new_node->value = value;
    new_node->next = next;
    return new_node;
}

node *create_linked_list(int nodes) {
    /* Create a singly linked list by creating a tail
     * node with a zero value and then creating a specified amount
     * of nodes with an incremented value that will point to the
     * latest created node. */
    int i, length = nodes;
    node *node_pointer = NULL;
    for (i = 0; i < length; i++) {
        node_pointer = create_node(i, node_pointer);
    }
    return node_pointer;
}

void print_linked_list(node *node_pointer) {
    while (node_pointer != NULL) {
        printf("%d\n", node_pointer->value);
        node_pointer = node_pointer->next;
    }
}

node *get_kth_to_last(node *node_pointer, int k) {
    int i;
    node *runner_pointer = node_pointer;
    if (node_pointer == NULL) {
        fprintf(
            stderr, "You passed a null pointer to "
                    "get_kth_to_last, don't do that\n"
        );
        exit(1);
    }
    for (i = 0; i < k; i++) {
        runner_pointer = runner_pointer->next;
        if (runner_pointer == NULL) {
            fprintf(
                stderr, "Out of bounds! The specified offset "
                        "is larger than the amount of nodes "
                        "in the linked list\n"
            );
            exit(1);
        }
    }

    while (runner_pointer->next != NULL) {
        node_pointer = node_pointer->next;
        runner_pointer = runner_pointer->next;
    }

    return node_pointer;
}

void test_return_kth_to_last() {
    node *elem;

    node *root = create_linked_list(10);

    printf("The linked list looks like:\n");
    print_linked_list(root);

    elem = get_kth_to_last(root, 0);
    printf("The 0th to last element has value %d\n", elem->value);
    assert(elem->value == 0);

    elem = get_kth_to_last(root, 3);
    printf("The third to last element has value %d\n", elem->value);
    assert(elem->value == 3);

    elem = get_kth_to_last(root, 8);
    printf("The eight to last element has value %d\n", elem->value);
    assert(elem->value == 8);
}

int main(void) {
    test_return_kth_to_last();
    return 0;
}
