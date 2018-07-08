#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Check if a linked list is a palindrome */

/*
$ gcc q2_6.c && ./a.out
Linked list under test looks like: test string
Asserting it is NOT a palindrome
Linked list under test looks like: a
Asserting it IS a palindrome
Linked list under test looks like: aba
Asserting it IS a palindrome
Linked list under test looks like: abc
Asserting it is NOT a palindrome
Linked list under test looks like: abba
Asserting it IS a palindrome
Linked list under test looks like: abbc
Asserting it is NOT a palindrome
Linked list under test looks like: abbaabba
Asserting it IS a palindrome
Linked list under test looks like: abcabc
Asserting it is NOT a palindrome
Linked list under test looks like: abcabca
Asserting it is NOT a palindrome
*/


/* Note: these statement expression macros are not standard C99 but a GCC
 * extension. You can write it out by hand but for the sake of brevity
 * this bit of metaprogramming here will allow us to abstract some logic
 * easily instead of having to loop over a multi-dimensional array of
 * strings and ints*/
#define assert_palindrome(string, should_be_palindrome) ({ \
    root_pointer = create_string_literal_linked_list(string); \
    printf("Linked list under test looks like: "); \
    print_linked_list(root_pointer); \
    if (should_be_palindrome) { \
        printf("Asserting it IS a palindrome\n"); \
    } else { \
        printf("Asserting it is NOT a palindrome\n"); \
    } \
    assert(is_palindrome(root_pointer) == should_be_palindrome); \
    free(root_pointer); \
})

typedef struct node_struct {
    char value;
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

node *init_or_add_left(node *node_pointer, int value) {
    if (node_pointer == NULL) {
        node_pointer = create_node(value);
    } else {
        node_pointer = add_left(node_pointer, value);
    }
    return node_pointer;
}

void print_linked_list(node *node_pointer) {
    while (node_pointer != NULL) {
        printf("%c", node_pointer->value);
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
    if (node_pointer->prev != NULL) {
        fprintf(
            stderr, "Please only pass a root node pointers, not a "
                    "node with a previous node attached!\n"
        );
        exit(1);
    }
}

int is_palindrome(node *left_pointer) {
    /* Test if a double linked list is a palindrome.
     * Returns 1 if it is, 0 if it is not. */
    assert_valid_node(left_pointer);
    if (left_pointer->next == NULL) {
        return 1;
    }

    node *right_pointer = left_pointer;
    while (right_pointer->next != NULL && right_pointer->next->next != NULL) {
        left_pointer = left_pointer->next;
        right_pointer = right_pointer->next->next;
    }
    if (right_pointer->next == NULL) {
        /* The string has an uneven amount of chars */
        left_pointer = left_pointer->prev;
        right_pointer = left_pointer->next->next;
    } else {
        /* The string has an even amount of chars */
        right_pointer = left_pointer->next;
    }
    while (left_pointer != NULL && right_pointer != NULL) {
        if (left_pointer->value != right_pointer->value) {
            return 0;
        }
        left_pointer = left_pointer->prev;
        right_pointer = right_pointer->next;
    }
    return 1;
}

node *create_string_literal_linked_list(char str[]) {
    int len = strlen(str) - 1, i;
    node *node_pointer = NULL;
    for (i = len; i >= 0; i--) {
        node_pointer = init_or_add_left(node_pointer, str[i]);
    }
    return node_pointer;
}

void test_is_palindrome() {
    node *root_pointer;

    assert_palindrome("test string", 0);
    assert_palindrome("a", 1);
    assert_palindrome("aba", 1);
    assert_palindrome("abc", 0);
    assert_palindrome("abba", 1);
    assert_palindrome("abbc", 0);
    assert_palindrome("abbaabba", 1);
    assert_palindrome("abcabc", 0);
    assert_palindrome("abcabca", 0);
}

int main(void) {
    test_is_palindrome();
    return 0;
}
