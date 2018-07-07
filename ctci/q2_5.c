#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <assert.h>

/* Add two linked lists where each node represents
 * one digit to a new linked list where each node
 * also represents one digital. Do that for the
 * the numbers represented in the linked list both
 * in forward and backward order.
 * I.e.: 717 + 395 = 912 in forward order
 * 7 -> 1 -> 6 + 5 -> 9 -> 2 = 2 -> 1 -> 9
 * and in backward order
 * 6 -> 1 -> 7 + 2 -> 9 -> 5 = 9 -> 1 -> 2 */

/*
$ gcc q2_5.c -lm && ./a.out
The first linked list for value 27197232 looks like:
2 3 2 7 9 1 7 2
Verifying Int transform to the first linked list is correct
The second linked list for value 271835229 looks like:
9 2 2 5 3 8 1 7 2
Verifying Int transform to the third linked list is correct
The added linked list that should hold value 299032461 looks like:
1 6 4 2 3 0 9 9 2
Verifying Int transform to the added linked list is correct

The first linked list for value 382504694 looks like:
3 8 2 5 0 4 6 9 4
Verifying Int transform to the first linked list is correct
The second linked list for value 52078970 looks like:
5 2 0 7 8 9 7 0
Verifying Int transform to the third linked list is correct
The added linked list that should hold value 434583664 looks like:
4 3 4 5 8 3 6 6 4
Verifying Int transform to the added linked list is correct
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

int digits_in_unsigned_int(unsigned int number) {
    if (number == 0) {
        return 1;
    } else {
        return floor(log10(number)) + 1;
    }
}

node *int_to_linked_list(unsigned int number, int forward) {
    int buf_size = digits_in_unsigned_int(number);
    int digits[buf_size], i;
    node *root_pointer, *node_pointer = NULL;
    for (i = number; i > 0; i /= 10) {
        if (node_pointer == NULL) {
            root_pointer = node_pointer = create_node(i % 10);
        } else {
            if (forward) {
                node_pointer = add_left(node_pointer, i % 10);
            } else {
                node_pointer = add_right(node_pointer, i % 10);
            }

        }
    }
    if (forward) {
        return node_pointer;
    } else {
        return root_pointer;
    }
}

int linked_list_to_int(node *node_pointer, int forward) {
    int value = 0, multiplier = 1;
    if (forward) {
        while (node_pointer->next != NULL) {
            node_pointer = node_pointer->next;
        }
    }
    while (node_pointer != NULL) {
        value += node_pointer->value * multiplier;
        if (forward) {
            node_pointer = node_pointer->prev;
        } else {
            node_pointer = node_pointer->next;
        }
        multiplier *= 10;
    }
    return value;
}

node *init_or_add_right(node *node_pointer, int value) {
    if (node_pointer == NULL) {
        node_pointer = create_node(value);
    } else {
        node_pointer = add_right(node_pointer, value);
    }
    return node_pointer;
}

node *add_backward_linked_lists(node *first_node_pointer, node *second_node_pointer) {
    int value = 0;
    node *root_pointer = NULL, *node_pointer = NULL;
    while (first_node_pointer != NULL || second_node_pointer != NULL) {
        if (first_node_pointer) {
            value += first_node_pointer->value;
        }
        if (second_node_pointer) {
            value += second_node_pointer->value;
        }

        if (value > 9) {
            node_pointer = init_or_add_right(node_pointer, value - 10);
            value = 1;
        } else {
            node_pointer = init_or_add_right(node_pointer, value);
            value = 0;
        }

        if (first_node_pointer) {
            first_node_pointer = first_node_pointer->next;
        }
        if (second_node_pointer) {
            second_node_pointer = second_node_pointer->next;
        }

        if (root_pointer == NULL) {
            root_pointer = node_pointer;
        }
    }
    if (value) {
        add_right(node_pointer, 1);
    }
    return root_pointer;
}

node *add_forward_linked_lists(node *first_node_pointer, node *second_node_pointer) {
    int value;
    node *root_pointer = NULL, *node_pointer = NULL, *increment_pointer;
    while (first_node_pointer != NULL || second_node_pointer != NULL) {
        value = 0;
        if (first_node_pointer) {
            value += first_node_pointer->value;
        }
        if (second_node_pointer) {
            value += second_node_pointer->value;
        }

        increment_pointer = node_pointer = init_or_add_right(
                node_pointer, value
        );
        if (value > 9) {
            while (increment_pointer->value > 9) {
                if (increment_pointer->prev == NULL) {
                    root_pointer = add_left(increment_pointer, 1);
                } else {
                    increment_pointer->prev->value += 1;
                }
                increment_pointer->value %= 10;
                increment_pointer = increment_pointer->prev;
            }
        }

        if (first_node_pointer) {
            first_node_pointer = first_node_pointer->next;
        }
        if (second_node_pointer) {
            second_node_pointer = second_node_pointer->next;
        }

        if (root_pointer == NULL) {
            root_pointer = node_pointer;
        }
    }
    return root_pointer;
}

int linked_list_length(node *node_pointer) {
    int count = 0;
    while (node_pointer != NULL) {
        count++;
        node_pointer = node_pointer->next;
    }
    return count;
}

node *pad_linked_list(node *node_pointer, int cur_length, int new_length) {
    int pad_count, i;
    if (cur_length < new_length) {
        pad_count = new_length - cur_length;
        for (i = 0; i < pad_count; i++) {
            node_pointer = add_left(node_pointer, 0);
        }
    }
    return node_pointer;
}

node *add_linked_lists(node *first_node_pointer, node *second_node_pointer, int forward) {
    node *node_pointer;
    if (forward) {
        int ll1_length = linked_list_length(first_node_pointer);
        int ll2_length = linked_list_length(second_node_pointer);
        int max_ll_length = ll1_length > ll2_length ? ll1_length : ll2_length;
        first_node_pointer = pad_linked_list(
            first_node_pointer, ll1_length, max_ll_length
        );
        second_node_pointer = pad_linked_list(
            second_node_pointer, ll2_length, max_ll_length
        );
        node_pointer = add_forward_linked_lists(
            first_node_pointer, second_node_pointer
        );
    } else {
        node_pointer = add_backward_linked_lists(
            first_node_pointer, second_node_pointer
        );
    }
    return node_pointer;
}

void test_added_linked_lists(int forward) {
    unsigned int first_value = rand() % (UINT_MAX / 10);
    unsigned int second_value = rand() % (UINT_MAX / 10);
    node *ll1, *ll2, *ll3;
    ll1 = int_to_linked_list(first_value, forward);
    printf("The first linked list for value %d looks like:\n", first_value);
    print_linked_list(ll1);
    printf("Verifying Int transform to the first linked list is correct\n");
    assert(linked_list_to_int(ll1, forward) == first_value);
    ll2 = int_to_linked_list(second_value, forward);
    printf("The second linked list for value %d looks like:\n", second_value);
    print_linked_list(ll2);
    printf("Verifying Int transform to the third linked list is correct\n");
    assert(linked_list_to_int(ll2, forward) == second_value);
    ll3 = add_linked_lists(ll1, ll2, forward);
    printf(
        "The added linked list that should hold value %d looks like:\n",
        first_value + second_value
    );
    print_linked_list(ll3);
    printf("Verifying Int transform to the added linked list is correct\n");
    assert(linked_list_to_int(ll3, forward) == first_value + second_value);
    printf("\n");
}

int main(void) {
    srand(time(NULL));
    test_added_linked_lists(0);
    test_added_linked_lists(1);
    return 0;
}
