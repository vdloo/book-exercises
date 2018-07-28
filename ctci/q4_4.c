#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Implement a function to check if a binary tree is balanced. For this exercise
 * a balanced binary tree is defined such that the heights of the two subtrees of
 * any node never differ more than one */

/*
$ gcc q4_4.c && ./a.out
Testing if balanced binary tree 1 reports as balanced
Testing if balanced binary tree 2 reports as balanced
Testing if balanced binary tree 3 reports as balanced
Testing if balanced binary tree 4 reports as balanced
Testing if balanced binary tree 5 reports as balanced
Testing if unbalanced binary tree 1 reports as unbalanced
Testing if unbalanced binary tree 2 reports as unbalanced
*/


typedef struct node_struct {
    struct node_struct *left;
    struct node_struct *right;
} node;

node *create_node() {
    node * new_node = NULL;
    new_node = malloc(sizeof(node));
    if (new_node == NULL) {
        fprintf(
            stderr, "Failed to allocate memory for "
                    "new node in linked list\n"
        );
        exit(1);
    }
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

node *balanced_binary_tree_1() {
    node *node_pointer = create_node();
    node_pointer->left = create_node();
    node_pointer->right = create_node();
    return node_pointer;
}

node *balanced_binary_tree_2() {
    node *node_pointer = create_node();
    node_pointer->left = create_node();
    node_pointer->left->left = create_node();
    node_pointer->right = create_node();
    return node_pointer;
}

node *balanced_binary_tree_3() {
    node *node_pointer = create_node();
    node_pointer->left = create_node();
    node_pointer->left->left = create_node();
    node_pointer->right = create_node();
    node_pointer->right->right = create_node();
    return node_pointer;
}

node *balanced_binary_tree_4() {
    node *node_pointer = create_node();
    node_pointer->left = create_node();
    node_pointer->left->left = create_node();
    node_pointer->left->right = create_node();
    node_pointer->right = create_node();
    node_pointer->right->right = create_node();
    return node_pointer;
}

node *balanced_binary_tree_5() {
    node *node_pointer = create_node();
    node_pointer->left = create_node();
    node_pointer->left->left = create_node();
    node_pointer->left->right = create_node();
    node_pointer->right = create_node();
    node_pointer->right->left = create_node();
    node_pointer->right->right = create_node();
    return node_pointer;
}

node *unbalanced_binary_tree_1() {
    node *node_pointer = create_node();
    node_pointer->left = create_node();
    node_pointer->left->left = create_node();
    return node_pointer;
}

node *unbalanced_binary_tree_2() {
    node *node_pointer = create_node();
    node_pointer->left = create_node();
    node_pointer->right = create_node();
    node_pointer->right->left = create_node();
    node_pointer->right->left->left = create_node();
    node_pointer->right->right = create_node();
    return node_pointer;
}

int is_balanced_iter(node *node_pointer, int count) {
    int left_height, right_height;
    if (node_pointer == NULL) {
        return count;
    }
    left_height = is_balanced_iter(node_pointer->left, count + 1);
    if (left_height == -1) {
        return -1;
    }
    right_height = is_balanced_iter(node_pointer->right, count + 1);
    if (right_height == -1) {
        return -1;
    }
    if (left_height - right_height > 1 || right_height - left_height > 1) {
        return - 1;
    }
    return left_height > right_height ? left_height : right_height;
}

int is_balanced(node *node_pointer) {
    /* Returns 1 if balanced, 0 if not */
    return is_balanced_iter(node_pointer, 0) != -1;
}

int main(void) {
    printf("Testing if balanced binary tree 1 reports as balanced\n");
    assert(is_balanced(balanced_binary_tree_1()));
    printf("Testing if balanced binary tree 2 reports as balanced\n");
    assert(is_balanced(balanced_binary_tree_2()));
    printf("Testing if balanced binary tree 3 reports as balanced\n");
    assert(is_balanced(balanced_binary_tree_3()));
    printf("Testing if balanced binary tree 4 reports as balanced\n");
    assert(is_balanced(balanced_binary_tree_4()));
    printf("Testing if balanced binary tree 5 reports as balanced\n");
    assert(is_balanced(balanced_binary_tree_5()));
    printf("Testing if unbalanced binary tree 1 reports as unbalanced\n");
    assert(is_balanced(unbalanced_binary_tree_1()) == 0);
    printf("Testing if unbalanced binary tree 2 reports as unbalanced\n");
    assert(is_balanced(unbalanced_binary_tree_2()) == 0);
    return 0;
}

