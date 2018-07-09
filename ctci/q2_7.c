#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Given two singly linked lists, return the
 * intersecting node or NULL if it does not
 * intersect */

/*
$ gcc q2_7.c && ./a.out
The first linked list looks like: 01234567
The second linked list looks like: 01234567891011
The third linked list looks like: 01234
The third list with intersection looks like: 012344567
Asserting the first linked list does not intersect with the second
Asserting the second linked list does not intersect with the first
Asserting the second linked list does not intersect with the third
Asserting the third linked list does not intersect with the second
Asserting the first linked list intersects with the third
Asserting the third linked list intersects with the first
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

#define find_tail(tail_node_pointer, length, node_pointer) ({ \
    assert_valid_node(node_pointer); \
    while (tail_node_pointer->next != NULL) { \
        length++; \
        tail_node_pointer = tail_node_pointer->next; \
    } \
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

node *fast_forward(node *node_pointer, int count) {
    int i;
    for (i = 0; i < count; i++) {
        node_pointer = node_pointer->next;
    }
    return node_pointer;
}

node *find_intersection(node *first_node_pointer, node *second_node_pointer) {
    node *first_tail = first_node_pointer, *second_tail = second_node_pointer;
    int first_length = 0, second_length = 0, i;
    find_tail(first_tail, first_length, first_node_pointer);
    find_tail(second_tail, second_length, second_node_pointer);
    if (first_tail != second_tail) {
        /* If the tails do not point to the same memory location,
         * then there is no intersection. If there was an intersection
         * both linked lists would end in the same node (they can have
         * different beginnings but must have the same end) */
        return NULL;
    }
    if (first_length > second_length) {
        first_node_pointer = fast_forward(
            first_node_pointer, first_length - second_length
        );
    } else {
        second_node_pointer = fast_forward(
            second_node_pointer, second_length - first_length
        );
    }
    while (first_node_pointer != NULL  && second_node_pointer != NULL) {
        if (first_node_pointer == second_node_pointer) {
            return first_node_pointer;
        }
        first_node_pointer = first_node_pointer->next;
        second_node_pointer = second_node_pointer->next;
    }
    fprintf(
        stderr, "Fell of the end of one of the linked lists! That should "
                "never happen, you made a programming error!\n"
    );
    exit(1);
}

void test_intersects() {
    int i;
    node *ll1, *ll2, *ll3, *tmp;
    ll1 = ll2 = ll3 = NULL;

    declare_linked_list(ll1, "first", 8);
    declare_linked_list(ll2, "second", 12);
    declare_linked_list(ll3, "third", 5);
    tmp->next = ll1->next->next->next->next;

    printf("The third list with intersection looks like: ");
    print_linked_list(ll3);

    printf(
        "Asserting the first linked list does not intersect with the second\n"
    );
    assert(find_intersection(ll1, ll2) == NULL);
    printf(
        "Asserting the second linked list does not intersect with the first\n"
    );
    assert(find_intersection(ll2, ll1) == NULL);
    printf(
        "Asserting the second linked list does not intersect with the third\n"
    );
    assert(find_intersection(ll2, ll3) == NULL);
    printf(
        "Asserting the third linked list does not intersect with the second\n"
    );
    assert(find_intersection(ll3, ll2) == NULL);
    printf(
        "Asserting the first linked list intersects with the third\n"
    );
    assert(find_intersection(ll1, ll3) == tmp->next);
    printf(
        "Asserting the third linked list intersects with the first\n"
    );
    assert(find_intersection(ll1, ll3) == tmp->next);
}

int main(void) {
    test_intersects();
    return 0;
}
