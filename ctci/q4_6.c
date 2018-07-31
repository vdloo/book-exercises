#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Write an algorithm to find the successor node in a binary search tree */

/*
$ gcc q4_6.c && ./a.out
Testing if successor to 11 is 12
Testing if successor to 10 is 11
Testing if successor to 5 is 6
Testing if successor to 2 is 3
Testing if successor to 6 is 7
Testing if successor to 12 is -1 (no successor)
*/


typedef struct node_struct {
    int value;
    struct node_struct *left;
    struct node_struct *right;
    struct node_struct *parent;
} node;

node *create_node(int value, node *parent) {
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
    new_node->parent = parent;
    return new_node;
}

node *bst() {
    /* BST looks like:
     *               7
     *          4        9
     *       3      6        11
     *    2       5       10    12
     */
    node *node_pointer = create_node(7, NULL);
    node_pointer->left = create_node(4, node_pointer);
    node_pointer->left->left = create_node(3, node_pointer->left);
    node_pointer->left->left->left = create_node(2, node_pointer->left->left);
    node_pointer->right = create_node(9, node_pointer);
    node_pointer->left->right = create_node(6, node_pointer->left);
    node_pointer->left->right->left = create_node(
        5, node_pointer->left->right
    );
    node_pointer->right->right = create_node(11, node_pointer->right);
    node_pointer->right->right->left = create_node(
        10, node_pointer->right->right
    );
    node_pointer->right->right->right = create_node(
        12, node_pointer->right->right
    );
    return node_pointer;
}

int get_most_left(node *node_pointer) {
    node *tmp = node_pointer;
    while (tmp->left != NULL) {
        tmp = tmp->left;
    }
    return tmp->value;
}

int get_first_right_parent(node *node_pointer) {
    node *search_pointer = node_pointer;
    while (search_pointer->parent != NULL) {
        if (search_pointer->parent->left == search_pointer) {
            return search_pointer->parent->value;
        }
        search_pointer = search_pointer->parent;
    }
    return -1;
}

int get_successor(node *node_pointer) {
    if (node_pointer == NULL) {
        fprintf(stderr, "Don't pass a NULL pointer\n");
        exit(1);
    }
    if (node_pointer->right == NULL) {
        if (node_pointer->parent->left == node_pointer) {
            return node_pointer->parent->value;
        } else {
            return get_first_right_parent(node_pointer->parent);
        }
    } else {
        return get_most_left(node_pointer->right);
    }
}

int main(void) {
    node *my_bst = bst();
    printf("Testing if successor to 11 is 12\n");
    assert(get_successor(my_bst->right->right) == 12);
    printf("Testing if successor to 10 is 11\n");
    assert(get_successor(my_bst->right->right->left) == 11);
    printf("Testing if successor to 5 is 6\n");
    assert(get_successor(my_bst->left->right->left) == 6);
    printf("Testing if successor to 2 is 3\n");
    assert(get_successor(my_bst->left->left->left) == 3);
    printf("Testing if successor to 6 is 7\n");
    assert(get_successor(my_bst->left->right) == 7);
    printf("Testing if successor to 12 is -1 (no successor)\n");
    assert(get_successor(my_bst->right->right->right) == -1);
    return 0;
}

