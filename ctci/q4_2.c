#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Create a binary search tree with minimal height based on an
 * array that is sorted in increased order and only contains
 * unique integer elements. */

/*
$ gcc q4_2.c -lm && ./a.out
Binary search tree for 1 2 3 looks like:
2
1 3
Binary search tree for 1 2 3 4 5 6 looks like:
3
1 5
2 4 6
Binary search tree for 1 3 4 5 6 8 9 looks like:
5
3 8
1 4 6 9
Binary search tree for -10 3 5 10 11 15 16 looks like:
10
3 15
-10 5 11 16
*/

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

node *binary_search_tree(int array[], int size) {
    return binary_search_tree_iter(array, 0, size - 1);
}

/* queue implementation for printing the tree (no proper indenting though) */
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
    free(tmp);
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

node *queue_remove(stack **queue_forward, stack **queue_backward) {
    flush_forward_to_backward(queue_forward, queue_backward);
    return pop(queue_backward);
}

void print_tree_iter(stack **queue_forward, stack **queue_backward) {
    node *value;
    stack *next_queue_forward = NULL;
    stack *next_queue_backward = NULL;
    while (*queue_forward != NULL || *queue_backward != NULL) {
        value = queue_remove(queue_forward, queue_backward);
        printf("%d ", value->value);
        if (value->left != NULL) {
            queue_add(&next_queue_forward, &next_queue_backward, value->left);
        }
        if (value->right != NULL) {
            queue_add(&next_queue_forward, &next_queue_backward, value->right);
        }
    }
    printf("\n");
    if (next_queue_forward != NULL || next_queue_forward != NULL) {
        print_tree_iter(&next_queue_forward, &next_queue_backward);
    }
}

void print_tree(node *node_pointer) {
    stack *queue_forward = NULL;
    stack *queue_backward = NULL;
    queue_add(&queue_forward, &queue_backward, node_pointer);
    print_tree_iter(&queue_forward, &queue_backward);
}

void test_array_0_binary_search_tree() {
    node *root_pointer;
    root_pointer = binary_search_tree(array0, array_0_size);
    printf("Binary search tree for 1 2 3 looks like:\n");
    print_tree(root_pointer);
    assert(root_pointer->value == 2);
    assert(root_pointer->left->value == 1);
    assert(root_pointer->right->value == 3);
    assert(root_pointer->left->left == NULL);
    assert(root_pointer->left->right == NULL);
    assert(root_pointer->right->left == NULL);
    assert(root_pointer->left->right == NULL);
}

void test_array_1_binary_search_tree() {
    node *root_pointer;
    root_pointer = binary_search_tree(array1, array_1_size);
    printf("Binary search tree for 1 2 3 4 5 6 looks like:\n");
    print_tree(root_pointer);
    assert(root_pointer->value == 3);
    assert(root_pointer->left->value == 1);
    assert(root_pointer->left->left == NULL);
    assert(root_pointer->left->right->value == 2);
    assert(root_pointer->left->right->left == NULL);
    assert(root_pointer->left->right->right == NULL);
    assert(root_pointer->right->value == 5);
    assert(root_pointer->right->left->value == 4);
    assert(root_pointer->right->left->left == NULL);
    assert(root_pointer->right->left->right == NULL);
    assert(root_pointer->right->right->value == 6);
    assert(root_pointer->right->right->left == NULL);
    assert(root_pointer->right->right->right == NULL);
}

void test_array_2_binary_search_tree() {
    node *root_pointer;
    root_pointer = binary_search_tree(array2, array_2_size);
    printf("Binary search tree for 1 3 4 5 6 8 9 looks like:\n");
    print_tree(root_pointer);
    assert(root_pointer->value == 5);
    assert(root_pointer->left->value == 3);
    assert(root_pointer->left->left->value == 1);
    assert(root_pointer->left->left->left == NULL);
    assert(root_pointer->left->left->right == NULL);
    assert(root_pointer->left->right->value == 4);
    assert(root_pointer->left->right->left == NULL);
    assert(root_pointer->left->right->right == NULL);
    assert(root_pointer->right->value == 8);
    assert(root_pointer->right->left->value == 6);
    assert(root_pointer->right->left->left == NULL);
    assert(root_pointer->right->left->right == NULL);
    assert(root_pointer->right->right->value == 9);
    assert(root_pointer->right->right->left == NULL);
    assert(root_pointer->right->right->right == NULL);
}

void test_array_3_binary_search_tree() {
    node *root_pointer;
    root_pointer = binary_search_tree(array3, array_3_size);
    printf("Binary search tree for -10 3 5 10 11 15 16 looks like:\n");
    print_tree(root_pointer);
    assert(root_pointer->value == 10);
    assert(root_pointer->left->value == 3);
    assert(root_pointer->left->left->value == -10);
    assert(root_pointer->left->left->left == NULL);
    assert(root_pointer->left->left->right == NULL);
    assert(root_pointer->left->right->value == 5);
    assert(root_pointer->left->right->left == NULL);
    assert(root_pointer->left->right->right == NULL);
    assert(root_pointer->right->value == 15);
    assert(root_pointer->right->left->value == 11);
    assert(root_pointer->right->left->left == NULL);
    assert(root_pointer->right->left->right == NULL);
    assert(root_pointer->right->right->value == 16);
    assert(root_pointer->right->right->left == NULL);
    assert(root_pointer->right->right->right == NULL);
}

int main(void) {
    test_array_0_binary_search_tree();
    test_array_1_binary_search_tree();
    test_array_2_binary_search_tree();
    test_array_3_binary_search_tree();
    return 0;
}

