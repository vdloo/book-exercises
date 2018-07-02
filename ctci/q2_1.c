#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Remove duplicates from an unsorted linked list without using
 * a temporary buffer for holding previously seen values*/

/*
  $ gcc q2_1.c && ./a.out
  Checking sum_range function returns expected result
  Checking if linked list sums to the sum of 10 without any mutations
  Checking if linked list does not sum to the sum of 10 with a duplicate node
  Checking if linked list has no duplicates after removing them with at least 1 duplicate
  Checking if linked list has no duplicates after removing them with at least 2 duplicates
  Printing final linked list, it should have 7 items because in the tests there were 3 duplicates
  9
  3
  4
  6
  2
  1
  0
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

void print_linked_list(node *node_pointer) {
    while (node_pointer != NULL) {
        printf("%d\n", node_pointer->value);
        node_pointer = node_pointer->next;
    }
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

void remove_next(node *node_pointer) {
    node *node_to_remove;
    if (node_pointer->next == NULL) {
        fprintf(
            stderr, "Tried to remove the next node of the node that is "
                    "the tail of the linked list. Don't do that.\n"
        );
        exit(1);
    }
    node_to_remove = node_pointer->next;
    node_pointer->next = node_pointer->next->next;
    free(node_to_remove);
}

int has_duplicates(node *node_pointer) {
    int counter = 0;
    while(node_pointer != NULL) {
        counter++;
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

void remove_duplications(node *node_pointer) {
    node *runner_pointer, *previous_pointer;
    while (node_pointer != NULL) {
        runner_pointer = node_pointer->next;
        while (runner_pointer != NULL) {
            if (node_pointer->value == runner_pointer->value) {
                remove_next(previous_pointer);
                break;
            }
            previous_pointer = runner_pointer;
            runner_pointer = runner_pointer->next;
        }
        node_pointer = node_pointer->next;
    }
}

void test_remove_duplicates() {
    node *root = create_linked_list(10);

    printf("Checking sum_range function returns expected result\n");
    assert(sum_range(10) == 45);

    printf(
        "Checking if linked list sums to the sum of 10 without any mutations\n"
    );
    assert(sum_linked_list(root) == sum_range(10));

    printf(
        "Checking if linked list does not sum to "
        "the sum of 10 with a duplicate node\n"
    );
    root->next->next->value = 5;
    assert(sum_linked_list(root) != sum_range(10));

    printf(
        "Checking if linked list has no duplicates "
        "after removing them with at least 1 duplicate\n"
    );
    remove_duplications(root);
    assert(sum_linked_list(root) == sum_range(10) - 7);

    printf(
        "Checking if linked list has no duplicates "
        "after removing them with at least 2 duplicates\n"
    );
    root->next->value = 3;
    root->next->next->value = 4;
    remove_duplications(root);
    assert(sum_linked_list(root) == sum_range(10) - 7 - 8 - 5);

    printf(
        "Printing final linked list, it should have 7 items "
        "because in the tests there were 3 duplicates\n"
    );
    print_linked_list(root);
}

int main(void) {
    test_remove_duplicates();
    return 0;
}
