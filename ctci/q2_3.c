#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Remove a middle node from a singly linked list but
 * you only have 'access' to the node you're removing.
 * While this question is a bit vague I imagine they
 * meant that you can only set values on the node that
 * is being removed, but in case of c I still have to
 * 'free' a removed node, which would be the next one
 * if the idea is that you copy the values from the
 * next to the current one and then point the next
 * pointer to the node after the next.*/


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

int sum_linked_list(node *node_pointer) {
    int sum = 0;
    while(node_pointer != NULL) {
        sum += node_pointer->value;
        node_pointer = node_pointer->next;
    }
    return sum;
}

int sum_range(int n){
    int result = 0;
    while (n > 0) {
        n--;
        result += n;
    }
    return result;
}

 void remove_kth_but_can_only_access_kth(node *node_pointer, int k) {
    node *next_pointer;
    int i;
    for (i = 0; i < k; i++) {
        node_pointer = node_pointer->next;
        if (node_pointer->next == NULL) {
            fprintf(
                stderr, "You can only remove middle nodes, "
                        "you tried to remove the last node in "
                        "the linked list or a node higher than "
                        "the length of the list\n"
            );
            exit(1);
        }
    }
    node_pointer->value = node_pointer->next->value;
    next_pointer = node_pointer->next;
    node_pointer->next = node_pointer->next->next;
    /* According to the exercise we're not allowed to 'access'
     * the next node but I want to neatly clean up the used
     * memory anyway. It would go out of scope at the end of
     * the program but cleaning it up here is nicer */
    free(next_pointer);
}

void test_remove_kth() {
    node *root = create_linked_list(10);

    printf("The linked list looks like:\n");
    print_linked_list(root);

    printf(
        "Checking if linked list sums to the sum of 10 without any mutations\n"
    );
    assert(sum_linked_list(root) == sum_range(10));

    remove_kth_but_can_only_access_kth(root, 4);
    printf("The linked list without node 5 looks like:\n");
    print_linked_list(root);
    printf(
        "Checking if linked list value count is correct after removing the fifth "
        "element which contained value 5 (index 4)\n"
    );
    assert(sum_linked_list(root) == sum_range(10) - 5);
}

int main(void) {
    test_remove_kth();
    return 0;
}
