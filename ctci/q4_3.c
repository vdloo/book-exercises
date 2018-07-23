#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Given a binary tree, design an algorithm that creates a
 * linked list of all nodes at each depth. */

/*
This solution uses a queue to perform breadth-first pre-order
traversal of the tree and store each node of the BST in a
linked list in an array with at each slot a level of the tree
$ gcc q4_3.c && ./a.out
Testing if each level is as expected for BST of 1 2 3
Testing if each level is as expected for BST of 1 2 3 4 5 6
Testing if each level is as expected for BST of 1 3 4 5 6 8 9
Testing if each level is as expected for BST of -10 3 5 10 11 15 16
*/

#define MAX_TREE_HEIGHT 100


int array0[] = {1, 2, 3};
int array_0_size = 3;
int array1[] = {1, 2, 3, 4, 5, 6};
int array_1_size = 6;
int array2[] = {1, 3, 4, 5, 6, 8, 9};
int array_2_size = 7;
int array3[] = {-10, 3, 5, 10, 11, 15, 16};
int array_3_size = 7;

typedef struct node_struct {
    int value;
    struct node_struct *left;
    struct node_struct *right;
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
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

node *insert(node *node_pointer, int value, int right) {
    /* Insert a new value into the tree, pass right as 0
     * for it to be added on the left node, set it to 1
     * to have it added on the right node */
    node *new_node = create_node(value);
    if (right) {
        node_pointer->right = new_node;
    } else {
        node_pointer->left = new_node;
    }
    return new_node;
}

node *binary_search_tree_iter(int array[], int first, int last) {
    int mid_index = (first + last) / 2;
    int node_value = array[mid_index];
    node *new_node = NULL;
    if (last >= 0) {
        new_node = create_node(node_value);
    }
    if (last > first) {
        new_node->left = binary_search_tree_iter(array, first, mid_index - 1);
        new_node->right = binary_search_tree_iter(array, mid_index + 1, last);
    }
    return new_node;
}

/* A BST is also a binary tree so re-using this one from exercise 4.2 */
node *binary_search_tree(int array[], int size) {
    return binary_search_tree_iter(array, 0, size - 1);
}

/* queue implementation for storing all nodes at each depth */
typedef struct stack_struct {
    node *value;
    struct stack_struct *next;
} stack;

void push(stack **next, node *value) {
    stack *new_node = NULL;
    new_node = malloc(sizeof(value));
    if (new_node == NULL) {
        fprintf(
            stderr, "Failed to allocate memory for "
                    "new node in linked list\n"
        );
        exit(1);
    }
    new_node->next = *next;
    new_node->value = value;
    *next = new_node;
}

node *pop(stack **node_pointer) {
    node *value;
    stack *tmp;
    if (node_pointer == NULL) {
        fprintf(
            stderr, "You can not pop from an empty list!\n"
        );
        exit(1);
    }
    value = (*node_pointer)->value;
    tmp = *node_pointer;
    *node_pointer = (*node_pointer)->next;
    return value;
}

void flush_forward_to_backward(stack **queue_forward, stack **queue_backward) {
    while (*queue_forward != NULL) {
        push(queue_backward, pop(queue_forward));
    }
}

void queue_add(stack **queue_forward, stack **queue_backward, node *value) {
    flush_forward_to_backward(queue_backward, queue_forward);
    push(queue_forward, value);
}

node *queue_peek(stack *queue_forward, stack *queue_backward) {
    flush_forward_to_backward(&queue_forward, &queue_backward);
    return queue_backward->value;
}

void linked_list_at_depths_iter(
    stack **queue_forward,
    stack **queue_backward,
    int counter,
    stack **forward_lists[],
    stack **backward_lists[]
) {
    stack *next_queue_forward = NULL;
    stack *next_queue_backward = NULL;
    if (counter >= MAX_TREE_HEIGHT) {
        fprintf(
            stderr, "This function can only handle "
                    "trees with a height up to %d!\n"
                    "", MAX_TREE_HEIGHT
        );
        exit(1);
    }
    flush_forward_to_backward(queue_forward, queue_backward);
    forward_lists[counter] = queue_forward;
    backward_lists[counter] = queue_backward;
    stack *queue_runner = *queue_backward;
    while (queue_runner != NULL) {
        if (queue_runner->value->left != NULL) {
            queue_add(&next_queue_forward, &next_queue_backward, queue_runner->value->left);
        }
        if (queue_runner->value->right != NULL) {
            queue_add(&next_queue_forward, &next_queue_backward, queue_runner->value->right);
        }
        queue_runner = queue_runner->next;
    }
    if (next_queue_forward != NULL || next_queue_forward != NULL) {
        linked_list_at_depths_iter(
            &next_queue_forward, &next_queue_backward, counter + 1,
            forward_lists, backward_lists
        );
    }
}

void linked_list_at_depths(
    stack **forward_lists[], stack **backward_lists[], node *node_pointer
) {
    stack *queue_forward = NULL;
    stack *queue_backward = NULL;
    queue_add(&queue_forward, &queue_backward, node_pointer);
    linked_list_at_depths_iter(
        &queue_forward,
        &queue_backward,
        0,
        forward_lists,
        backward_lists
    );
}

void test_array_0_binary_search_tree() {
    printf("Testing if each level is as expected for BST of 1 2 3\n");
    node *node_pointer;
    node_pointer = binary_search_tree(array0, array_0_size);
    stack **before;
    stack **forward_lists[MAX_TREE_HEIGHT] = {NULL};
    stack **backward_lists[MAX_TREE_HEIGHT] = {NULL};
    linked_list_at_depths(forward_lists, backward_lists, node_pointer);
    stack **forward_list;
    stack **backward_list;
    forward_list = forward_lists[0];
    backward_list = backward_lists[0];
    node_pointer = queue_peek(*forward_list, *backward_list);
    assert(node_pointer->value == 2);
    forward_list = forward_lists[1];
    backward_list = backward_lists[1];
    node_pointer = queue_peek(*forward_list, *backward_list);
    assert(node_pointer->value == 1);
    node_pointer = queue_peek(*forward_list, (*backward_list)->next);
    assert(node_pointer->value == 3);
}

void test_array_1_binary_search_tree() {
    printf("Testing if each level is as expected for BST of 1 2 3 4 5 6\n");
    node *node_pointer;
    node_pointer = binary_search_tree(array1, array_1_size);
    stack **before;
    stack **forward_lists[MAX_TREE_HEIGHT] = {NULL};
    stack **backward_lists[MAX_TREE_HEIGHT] = {NULL};
    linked_list_at_depths(forward_lists, backward_lists, node_pointer);
    stack **forward_list;
    stack **backward_list;
    forward_list = forward_lists[0];
    backward_list = backward_lists[0];
    node_pointer = queue_peek(*forward_list, *backward_list);
    assert(node_pointer->value == 3);
    forward_list = forward_lists[1];
    backward_list = backward_lists[1];
    node_pointer = queue_peek(*forward_list, *backward_list);
    assert(node_pointer->value == 1);
    node_pointer = queue_peek(*forward_list, (*backward_list)->next);
    assert(node_pointer->value == 5);
    forward_list = forward_lists[2];
    backward_list = backward_lists[2];
    node_pointer = queue_peek(*forward_list, *backward_list);
    assert(node_pointer->value == 2);
    node_pointer = queue_peek(*forward_list, (*backward_list)->next);
    assert(node_pointer->value == 4);
    node_pointer = queue_peek(*forward_list, (*backward_list)->next->next);
    assert(node_pointer->value == 6);
}

void test_array_2_binary_search_tree() {
    printf("Testing if each level is as expected for BST of 1 3 4 5 6 8 9\n");
    node *node_pointer;
    node_pointer = binary_search_tree(array2, array_2_size);
    stack **before;
    stack **forward_lists[MAX_TREE_HEIGHT] = {NULL};
    stack **backward_lists[MAX_TREE_HEIGHT] = {NULL};
    linked_list_at_depths(forward_lists, backward_lists, node_pointer);
    stack **forward_list;
    stack **backward_list;
    forward_list = forward_lists[0];
    backward_list = backward_lists[0];
    node_pointer = queue_peek(*forward_list, *backward_list);
    assert(node_pointer->value == 5);
    forward_list = forward_lists[1];
    backward_list = backward_lists[1];
    node_pointer = queue_peek(*forward_list, *backward_list);
    assert(node_pointer->value == 3);
    node_pointer = queue_peek(*forward_list, (*backward_list)->next);
    assert(node_pointer->value == 8);
    forward_list = forward_lists[2];
    backward_list = backward_lists[2];
    node_pointer = queue_peek(*forward_list, *backward_list);
    assert(node_pointer->value == 1);
    node_pointer = queue_peek(*forward_list, (*backward_list)->next);
    assert(node_pointer->value == 4);
    node_pointer = queue_peek(*forward_list, (*backward_list)->next->next);
    assert(node_pointer->value == 6);
    node_pointer = queue_peek(
        *forward_list, (*backward_list)->next->next->next
    );
    assert(node_pointer->value == 9);
}

void test_array_3_binary_search_tree() {
    printf(
        "Testing if each level is as expected for BST of -10 3 5 10 11 15 16\n"
    );
    node *node_pointer;
    node_pointer = binary_search_tree(array3, array_3_size);
    stack **before;
    stack **forward_lists[MAX_TREE_HEIGHT] = {NULL};
    stack **backward_lists[MAX_TREE_HEIGHT] = {NULL};
    linked_list_at_depths(forward_lists, backward_lists, node_pointer);
    stack **forward_list;
    stack **backward_list;
    forward_list = forward_lists[0];
    backward_list = backward_lists[0];
    node_pointer = queue_peek(*forward_list, *backward_list);
    assert(node_pointer->value == 10);
    forward_list = forward_lists[1];
    backward_list = backward_lists[1];
    node_pointer = queue_peek(*forward_list, *backward_list);
    assert(node_pointer->value == 3);
    node_pointer = queue_peek(*forward_list, (*backward_list)->next);
    assert(node_pointer->value == 15);
    forward_list = forward_lists[2];
    backward_list = backward_lists[2];
    node_pointer = queue_peek(*forward_list, *backward_list);
    assert(node_pointer->value == -10);
    node_pointer = queue_peek(*forward_list, (*backward_list)->next);
    assert(node_pointer->value == 5);
    node_pointer = queue_peek(*forward_list, (*backward_list)->next->next);
    assert(node_pointer->value == 11);
    node_pointer = queue_peek(
            *forward_list, (*backward_list)->next->next->next
    );
    assert(node_pointer->value == 16);
}

int main(void) {
    test_array_0_binary_search_tree();
    test_array_1_binary_search_tree();
    test_array_2_binary_search_tree();
    test_array_3_binary_search_tree();
    return 0;
}

