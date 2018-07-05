#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Partition a linked list around a value, such that all nodes
 * less than x come before all nodes greater than or equal to x.
 * If x is contained within the list, the values of x only need
 * to be right after the elements less than x (see below). The
 * partition element x can appear anywhere in the right part,
 * it does not need to appear between the left and right parts.
 * I.e.: 3 -> 5 -> 8 -> 5 -> 10 -> 2 -> 1 [partition = 5]
 * Becomes: 3 -> 1 -> 2 -> 10 -> 5 -> 5 -> 8 */

/*
$ gcc q2_4.c && ./a.out
The normal linked list looks like:
9 8 7 6 5 4 3 2 1 0
The partitioned normal linked list looks like:
0 1 2 3 4 9 8 7 6 5
Asserting that all after partition is higher for normal linked list
The mangled linked list looks like:
7 5 7 9 5 4 3 2 1 0
The partitioned mangled linked list looks like:
0 1 2 3 4 7 5 7 9 5
Asserting that all after partition is higher for mangled linked list
*/


typedef struct node_struct {
    int value;
    struct node_struct *next;
    struct node_struct *prev;
} node;

node *create_node(int value) {
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
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

node *add_left(node *node_pointer, int value) {
    /* Add a new node with the specified value on the left,
     * and return a pointer to the new root node */
    if (node_pointer->prev != NULL) {
        fprintf(
            stderr, "Can't add a node on the left! The previous "
                    "pointer of this node is not NULL\n"
        );
        exit(1);
    }
    node_pointer->prev = create_node(value);
    node_pointer->prev->next = node_pointer;
    return node_pointer->prev;
}

node *add_right(node *node_pointer, int value) {
    /* Add a new node with the specified value on the right,
     * and return a pointer to the new tail node */
    if (node_pointer->next != NULL) {
        fprintf(
            stderr, "Can't add a node on the right! The next "
                    "pointer of this node is not NULL\n"
        );
        exit(1);
    }
    node_pointer->next = create_node(value);
    node_pointer->next->prev = node_pointer;
    return node_pointer->next;
}

node *create_linked_list(int nodes) {
    /* Create a double linked list by creating a tail
     * node with a zero value and then creating a specified amount
     * of nodes with an incremented value that will point to the
     * latest created node and the previous node. */
    int i, length = nodes;
    node *next_pointer = create_node(0);
    for (i = 1; i < length; i++) {
        next_pointer = add_left(next_pointer, i);
    }
    return next_pointer;
}

void print_linked_list(node *node_pointer) {
    while (node_pointer != NULL) {
        printf("%d ", node_pointer->value);
        node_pointer = node_pointer->next;
    }
    printf("\n");
}

node *partition_linked_list(node *node_pointer, int partition_value) {
    if (node_pointer->prev != NULL) {
        fprintf(
            stderr, "Please only specify linked lists "
                    "by root node pointer\n"
        );
        exit(1);
    }
    node *root_node, *tail_node;
    root_node = tail_node = create_node(node_pointer->value);
    node_pointer = node_pointer->next;
    while(node_pointer != NULL) {
        if (node_pointer->value < partition_value) {
            root_node = add_left(root_node, node_pointer->value);
        } else {
            tail_node = add_right(tail_node, node_pointer->value);
        }
        node_pointer = node_pointer->next;
    }
    return root_node;
}

int all_after_partition_is_higher(node *node_pointer, int partition_value) {
    int after_partition = 0;
    while (node_pointer != NULL) {
        if (node_pointer->value == partition_value) {
            after_partition = 1;
        }
        if (after_partition && node_pointer->value < partition_value) {
            return 0;
        }
        node_pointer = node_pointer->next;
    }
    return 1;
}

void test_partition_linked_list() {
    int partition_value = 5;
    node *partitioned_root, *root = create_linked_list(10);

    printf("The normal linked list looks like:\n");
    print_linked_list(root);

    partitioned_root = partition_linked_list(root, partition_value);

    printf("The partitioned normal linked list looks like:\n");
    print_linked_list(partitioned_root);

    printf("Asserting that all after partition is higher for normal linked list\n");
    assert(all_after_partition_is_higher(partitioned_root, partition_value));


    root->value = 7;
    root->next->value = 5;
    root->next->next->next->value = 9;
    printf("The mangled linked list looks like:\n");
    print_linked_list(root);

    partitioned_root = partition_linked_list(root, partition_value);

    printf("The partitioned mangled linked list looks like:\n");
    print_linked_list(partitioned_root);

    printf("Asserting that all after partition is higher for mangled linked list\n");
    assert(all_after_partition_is_higher(partitioned_root, partition_value));
}

int main(void) {
    test_partition_linked_list();
    return 0;
}
