#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Check if a linked list has a loop and if so return the node
 * at the beginning of the loop. (This basically comes down to
 * 'implement Floyd's cycle-detection algorithm) */

/*
$ gcc q2_8.c && ./a.out
The no cycle linked list looks like: 0123456789
Asserting we don't find a cycle that linked list
Adding a cycle 9->3
Asserting we find a cycle and the correct node in the looped list
*/


#define declare_linked_list(variable, name, length) ({ \
    tmp = NULL; \
    for (i = 0; i < length; i++) { \
        tmp = init_or_add_right(tmp, i); \
        if (variable == NULL) { \
            variable = tmp; \
        } \
    } \
    printf("The %s linked list looks like: ", name); \
    print_linked_list(variable); \
})

typedef struct node_struct {
    char value;
    struct node_struct *next;
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
    return new_node;
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
    return node_pointer->next;
}

node *init_or_add_right(node *node_pointer, int value) {
    if (node_pointer == NULL) {
        node_pointer = create_node(value);
    } else {
        node_pointer = add_right(node_pointer, value);
    }
    return node_pointer;
}

void print_linked_list(node *node_pointer) {
    while (node_pointer != NULL) {
        printf("%d", node_pointer->value);
        node_pointer = node_pointer->next;
    }
    printf("\n");
}

void assert_valid_node(node *node_pointer) {
    if (node_pointer == NULL) {
        fprintf(
            stderr, "Please only pass a node pointer, not NULL!\n"
        );
        exit(1);
    }
}

/* Floyd's Tortoise and Hare */
node *find_cycle(node *node_pointer) {
    assert_valid_node(node_pointer);
    node *slow_pointer, *fast_pointer;
    slow_pointer = fast_pointer = node_pointer;
    while (fast_pointer && fast_pointer->next) {
        slow_pointer = slow_pointer->next;
        fast_pointer = fast_pointer->next->next;
        /* Detect if there is a loop */
        if (slow_pointer == fast_pointer) {
            /* Once the loop is detected, start incrementing the head
             * pointer and the runner pointer by one until they point
             * to the same node. That node will always exist because
             * the runner pointer will be a multiple of the steps that
             * were taken by the node pointer in the loop. It will be
             * just as far from the beginning of the loop as the head
             * pointer, so if we start incrementing both by one
             * inevitably they will meet. */
            while (node_pointer != fast_pointer) {
                node_pointer = node_pointer->next;
                fast_pointer = fast_pointer->next;
            }
            return node_pointer;
        }
    }
    return NULL;
}

void test_intersects() {
    int i;
    node *root = NULL, *tmp;

    declare_linked_list(root, "no cycle", 10);
    printf("Asserting we don't find a cycle that linked list\n");
    assert(find_cycle(root) == NULL);

    printf("Adding a cycle 9->3\n");
    tmp->next = root->next->next->next;
    printf(
        "Asserting we find a cycle and the correct node in the looped list\n"
    );
    assert(find_cycle(root) == tmp->next);
}

int main(void) {
    test_intersects();
    return 0;
}
