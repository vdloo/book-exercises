#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Implement a function to check if a binary tree is a binary search tree. A binary
 * search tree is a binary tree in which every node fits the ordering property:
 * all left descendants <= n < all right descendants for all nodes.
/*
$ gcc q4_5.c && ./a.out
Testing if bst 1 reports as a bst
Testing if bst 2 reports as a bst
Testing if bst 3 reports as a bst
Testing if bst 4 reports as a bst
Testing if bst 5 reports as a bst
Testing if bst 6 reports as a bst
Testing if not bst 1 reports as not a bst
Testing if not bst 2 reports as not a bst
Testing if not bst 3 reports as not a bst
*/


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

int is_bst_iter(node *node_pointer, int left_bound, int right_bound) {
    if (node_pointer == NULL) {
        return 1;
    }
    if (left_bound != -1 && node_pointer->value < left_bound) {
        return 0;
    }
    if (right_bound != -1 && node_pointer->value > right_bound) {
        return 0;
    }
    int left_is_bst = is_bst_iter(node_pointer->left, left_bound, node_pointer->value);
    int right_is_bst = is_bst_iter(node_pointer->right, node_pointer->value, right_bound);
    return left_is_bst && right_is_bst;
}

int is_bst(node *node_pointer) {
    /* Return 1 if is BST, 0 if not */
    return is_bst_iter(node_pointer, -1 , -1);
}

node *bst_1() {
    node *node_pointer = create_node(5);
    node_pointer->left = create_node(4);
    node_pointer->right = create_node(6);
    return node_pointer;
}

node *bst_2() {
    node *node_pointer = create_node(5);
    node_pointer->left = create_node(4);
    node_pointer->left->left = create_node(3);
    node_pointer->right = create_node(6);
    return node_pointer;
}

node *bst_3() {
    node *node_pointer = create_node(5);
    node_pointer->left = create_node(4);
    node_pointer->left->left = create_node(3);
    node_pointer->left->right = create_node(4);
    node_pointer->right = create_node(6);
    return node_pointer;
}

node *bst_4() {
    node *node_pointer = create_node(6);
    node_pointer->left = create_node(5);
    node_pointer->left->left = create_node(3);
    node_pointer->left->right = create_node(6);
    node_pointer->right = create_node(7);
    node_pointer->right->left = create_node(6);
    node_pointer->right->right = create_node(8);
    return node_pointer;
}

node *bst_5() {
    node *node_pointer = create_node(6);
    node_pointer->left = create_node(5);
    node_pointer->left->left = create_node(4);
    node_pointer->left->left->left = create_node(3);
    node_pointer->left->left->left->left = create_node(2);
    return node_pointer;
}

node *bst_6() {
    node *node_pointer = create_node(6);
    node_pointer->left = create_node(5);
    node_pointer->left->left = create_node(4);
    node_pointer->left->right = create_node(5);
    node_pointer->right = create_node(8);
    node_pointer->right->left = create_node(7);
    node_pointer->right->right = create_node(9);
    return node_pointer;
}

node *not_bst_1() {
    node *node_pointer = create_node(6);
    node_pointer->left = create_node(5);
    node_pointer->left->left = create_node(4);
    node_pointer->left->left->left = create_node(3);
    node_pointer->left->left->left->right = create_node(9);
    return node_pointer;
}

node *not_bst_2() {
    node *node_pointer = create_node(6);
    node_pointer->left = create_node(5);
    node_pointer->left->left = create_node(4);
    node_pointer->left->left->left = create_node(3);
    node_pointer->left->left->left->right = create_node(5);
    return node_pointer;
}

node *not_bst_3() {
    node *node_pointer = create_node(4);
    node_pointer->left = create_node(5);
    node_pointer->right = create_node(6);
    return node_pointer;
}

int main(void) {
    printf("Testing if bst 1 reports as a bst\n");
    assert(is_bst(bst_1()));
    printf("Testing if bst 2 reports as a bst\n");
    assert(is_bst(bst_2()));
    printf("Testing if bst 3 reports as a bst\n");
    assert(is_bst(bst_3()));
    printf("Testing if bst 4 reports as a bst\n");
    assert(is_bst(bst_4()));
    printf("Testing if bst 5 reports as a bst\n");
    assert(is_bst(bst_5()));
    printf("Testing if bst 6 reports as a bst\n");
    assert(is_bst(bst_6()));
    printf("Testing if not bst 1 reports as not a bst\n");
    assert(is_bst(not_bst_1()) == 0);
    printf("Testing if not bst 2 reports as not a bst\n");
    assert(is_bst(not_bst_2()) == 0);
    printf("Testing if not bst 3 reports as not a bst\n");
    assert(is_bst(not_bst_3()) == 0);
    return 0;
}

