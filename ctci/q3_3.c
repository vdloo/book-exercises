#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/* Implement a stack that creates a new stack if the current one
 * gets too big and the continues on that one. There should be a
 * function to push and pop to the 'set of stacks' that works the
 * same as if it was operating on one stack. Additionally there
 * should be a pop_at function that takes 'index' that can pop
 * from any of the sub-stacks. Make sure that when you pop from
 * a sub-stack all stacks are rolled-over so there won't be any
 * stack except for the last at less than full capacity. */

#define MAX_STACK_LENGTH 10

typedef struct node_struct {
    struct node_struct *value;
    struct node_struct *prev;
    struct node_struct *next;
    int count;
} node;

node *outer_stack = NULL;

node *create_node(node *value, int c) {
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
    new_node->prev = NULL;
    new_node->next = NULL;
    new_node->count = c;
    return new_node;
}

node *_push(node *node_pointer, node *value) {
    /* Add a new node with the specified value on the left,
     * and return a pointer to the new head node */
    int count;
    if (node_pointer == NULL) {
        count = 0;
    } else {
        count = node_pointer->count + 1;
    }
    node *new_node;
    new_node = create_node(value, count);
    new_node->prev = NULL;
    if (node_pointer) {
        node_pointer->prev = new_node;
    }
    new_node->next = node_pointer;
    return new_node;
}

node *_pop(node **node_pointer) {
    node *next;
    node *value;
    if (node_pointer == NULL) {
        fprintf(
            stderr, "Do not pass a NULL pointer to pop! Dereferencing "
                    "that would cause undef behavior!\n"
        );
        exit(1);
    }
    if (*node_pointer == NULL) {
        fprintf(
            stderr, "Can't operate on an empty stack!\n"
        );
        exit(1);
    }
    value = (*node_pointer)->value;
    next = (*node_pointer)->next;
    if (next != NULL) {
        next->prev = NULL;
    }
    free(*node_pointer);
    *node_pointer = next;
    return value;
}

node *peek(node *node_pointer) {
    if (node_pointer == NULL) {
        fprintf(
            stderr, "Can't operate on an empty stack!\n"
        );
        exit(1);
    }
    return node_pointer->value;
}

node *push(node *outer_stack, node *value) {
    node *inner_stack;
    if (outer_stack == NULL || outer_stack->value->count >= (MAX_STACK_LENGTH - 1)) {
        inner_stack = _push(NULL, value);
        outer_stack = _push(outer_stack, inner_stack);
    } else {
        outer_stack->value = _push(outer_stack->value, value);
    }
    return outer_stack;
}

node *pop(node **outer_stack) {
    if (*outer_stack == NULL) {
        fprintf(
            stderr, "Can't pop from empty outer stack!\n"
        );
        exit(1);
    }
    if ((*outer_stack)->value == NULL) {
        fprintf(
            stderr, "Can't pop from empty inner stack!\n"
        );
        exit(1);
    }
    node *value;
    value = _pop(&((*outer_stack)->value));
    if ((*outer_stack)->value == NULL) {
        _pop(outer_stack);
    }
    return value;
}

void test_pop_outer() {
    printf("Asserting pop outer works as intended\n");
    int i;
    node *node_to_add;
    outer_stack = NULL;
    for (i = 0; i < MAX_STACK_LENGTH; i++) {
        node_to_add = create_node(NULL, i);
        outer_stack = push(outer_stack, node_to_add);
    }
    assert(outer_stack->count == 0);
    assert(outer_stack->prev == NULL);
    assert(outer_stack->next == NULL);
    assert(outer_stack->value->count == (MAX_STACK_LENGTH - 1));
    assert(outer_stack->value->value->count == MAX_STACK_LENGTH - 1);
    assert(outer_stack->value->prev == NULL);
    assert(outer_stack->value->next != NULL);
    assert(outer_stack->value->next->count == MAX_STACK_LENGTH - 2);

    node_to_add = create_node(NULL, i);
    outer_stack = push(outer_stack, node_to_add);

    assert(outer_stack->count == 1);
    assert(outer_stack->value->count == 0);
    assert(outer_stack->value->value->count == MAX_STACK_LENGTH);
    assert(outer_stack->prev == NULL);
    assert(outer_stack->next != NULL);

    for (i = MAX_STACK_LENGTH; i >= 0; i--) {
        node_to_add = pop(&outer_stack);
        assert(node_to_add->count == i);
    }
}

void test_push_outer_two_nodes() {
    printf("Asserting push outer works as intended with two nodes\n");
    outer_stack = NULL;
    node *first_node_to_add = create_node(NULL, 1);
    node *second_node_to_add = create_node(NULL, 1);
    outer_stack = push(outer_stack, first_node_to_add);
    assert(outer_stack != NULL);
    assert(outer_stack->next == NULL);
    assert(outer_stack->prev == NULL);
    assert(outer_stack->value != NULL);
    assert(outer_stack->value->value == first_node_to_add);
    outer_stack = push(outer_stack, second_node_to_add);
    assert(outer_stack != NULL);
    assert(outer_stack->next == NULL);
    assert(outer_stack->prev == NULL);
    assert(outer_stack->value != NULL);
    assert(outer_stack->value->value == second_node_to_add);
    assert(outer_stack->value->next->value == first_node_to_add);
    free(outer_stack->value->next);
    free(outer_stack->value);
    free(outer_stack);
    free(first_node_to_add);
    free(second_node_to_add);
}

void test_push_outer_two_stacks() {
    printf("Asserting push outer works as intended with two inner stacks\n");
    int i;
    node *node_to_add = create_node(NULL, 1);
    outer_stack = NULL;
    for (i = 0; i < MAX_STACK_LENGTH; i++) {
        outer_stack = push(outer_stack, node_to_add);
    }
    assert(outer_stack != NULL);
    assert(outer_stack->next == NULL);
    assert(outer_stack->value->value == node_to_add);
    outer_stack = push(outer_stack, node_to_add);
    assert(outer_stack->next != NULL);
    assert(outer_stack->next->value->value == node_to_add);
    assert(outer_stack->next->next == NULL);
    for (i = 0; i < MAX_STACK_LENGTH; i++) {
        outer_stack = push(outer_stack, node_to_add);
    }
    assert(outer_stack->next->next != NULL);
    assert(outer_stack->next->next->value->value == node_to_add);
    assert(outer_stack->next->next->next == NULL);
    for (i = 0; i < ((MAX_STACK_LENGTH * 2) + 1); i++) {
        pop(&outer_stack);
    }
    assert(outer_stack == NULL);
}

void test_push_outer() {
    test_push_outer_two_nodes();
    test_push_outer_two_stacks();
}

void test_peek() {
    printf("Asserting peek works as intended\n");
    node *node_to_add = create_node(NULL, 1);
    node *node_under_test = _push(NULL, node_to_add);
    node *value;
    int i;
    for (i = 0; i < 2; i++) {
        value = peek(node_under_test);
        assert(value == node_to_add);
        assert(value->count == 1);
        assert(value->value == NULL);
        assert(value->prev == NULL);
        assert(value->next == NULL);
        assert(node_under_test != NULL);
    }
    free(value);
}

void test_pop_single_node() {
    printf("Asserting if we can pop from a list with a single node\n");
    node *node_to_add = create_node(NULL, 1);
    node *node_under_test = _push(NULL, node_to_add);
    node *value =_pop(&node_under_test);
    assert(value == node_to_add);
    assert(value->count == 1);
    assert(value->value == NULL);
    assert(value->prev == NULL);
    assert(value->next == NULL);
    assert(node_under_test == NULL);
    free(value);
}

void test_pop_two_nodes() {
    printf("Asserting if we can pop from a list with two nodes\n");
    node *first_node_to_add;
    node *second_node_to_add;
    node *first_node_under_test;
    node *second_node_under_test;
    node *value;
    first_node_to_add = create_node(NULL, 1);
    first_node_under_test = _push(NULL, first_node_to_add);
    second_node_to_add = create_node(NULL, 2);
    second_node_under_test = _push(first_node_under_test, second_node_to_add);
    assert(second_node_under_test != first_node_under_test);
    assert(second_node_under_test->count == 1);
    assert(second_node_under_test->next == first_node_under_test);
    assert(second_node_under_test->prev == NULL);
    value =_pop(&second_node_under_test);
    assert(value == second_node_to_add);
    assert(value->count == 2);
    assert(value->value == NULL);
    assert(value->prev == NULL);
    assert(value->next == NULL);
    free(value);
    /* we mutate the pointer of the node passed in to pop */
    assert(second_node_under_test == first_node_under_test);
    assert(first_node_under_test->count == 0);
    assert(first_node_under_test->next == NULL);
    assert(first_node_under_test->prev == NULL);
    value =_pop(&second_node_under_test);
    assert(value == first_node_to_add);
    assert(value->count == 1);
    assert(value->value == NULL);
    assert(value->prev == NULL);
    assert(value->next == NULL);
    assert(second_node_under_test == NULL);
    free(value);
}


void test_pop() {
    test_pop_single_node();
    test_pop_two_nodes();
}

void test_push_empty_to_empty_linked_list() {
    printf("Asserting if we can add an empty node to an empty linked list\n");
    node *node_under_test = _push(NULL, NULL);
    assert(node_under_test->count == 0);
    assert(node_under_test->value == NULL);
    assert(node_under_test->prev == NULL);
    assert(node_under_test->next == NULL);
    free(node_under_test);
}

void test_push_empty_to_existing_linked_list() {
    printf(
        "Asserting if we can add an empty node to an existing linked list\n"
    );
    node *existing_node = _push(NULL, NULL);
    node *node_under_test = _push(existing_node, NULL);
    assert(node_under_test->count == 1);
    assert(node_under_test->value == NULL);
    assert(node_under_test->prev == NULL);
    assert(node_under_test->next == existing_node);
    assert(existing_node->count == 0);
    assert(existing_node->value == NULL);
    assert(existing_node->prev == node_under_test);
    assert(existing_node->next == NULL);
    free(existing_node);
    free(node_under_test);
}

void test_push_node_to_empty_linked_list() {
    printf(
        "Asserting if we can add a node with value to an empty linked list\n"
    );
    node *node_to_add = create_node(NULL, 1);
    node *node_under_test = _push(NULL, node_to_add);
    assert(node_under_test->count == 0);
    assert(node_under_test->value == node_to_add);
    assert(node_under_test->prev == NULL);
    assert(node_under_test->next == NULL);
    assert(node_under_test->value->count == 1);
    assert(node_under_test->value->value == NULL);
    assert(node_under_test->value->prev == NULL);
    assert(node_under_test->value->next == NULL);
    free(node_to_add);
    free(node_under_test);
}

void test_push_node_to_existing_linked_list() {
    printf(
        "Asserting if we can add a node with "
        "value to an existing linked list\n"
    );
    node *node_to_add = create_node(NULL, 1);
    node *existing_node = _push(NULL, NULL);
    node *node_under_test = _push(existing_node, node_to_add);
    assert(node_under_test->count == 1);
    assert(node_under_test->value == node_to_add);
    assert(node_under_test->prev == NULL);
    assert(node_under_test->next == existing_node);
    assert(node_under_test->value->count == 1);
    assert(node_under_test->value->value == NULL);
    assert(node_under_test->value->prev == NULL);
    assert(node_under_test->value->next == NULL);
    assert(existing_node->count == 0);
    assert(existing_node->value == NULL);
    assert(existing_node->prev == node_under_test);
    assert(existing_node->next == NULL);
    free(existing_node);
    free(node_to_add);
    free(node_under_test);
}

void test_push() {
    test_push_empty_to_empty_linked_list();
    test_push_empty_to_existing_linked_list();
    test_push_node_to_empty_linked_list();
    test_push_node_to_existing_linked_list();
}

void test_creating_empty_node() {
    printf("Asserting if we can create an empty node\n");
    node *node_under_test = create_node(NULL, 1);
    assert(node_under_test->value == NULL);
    assert(node_under_test->prev == NULL);
    assert(node_under_test->next == NULL);
    assert(node_under_test->count == 1);
    free(node_under_test);
}

void test_create_node_with_value() {
    printf("Asserting if we can create a node with a value\n");
    node *node_value = create_node(NULL, 1);
    node *node_under_test = create_node(node_value, 2);
    assert(node_under_test->value == node_value);
    assert(node_under_test->prev == NULL);
    assert(node_under_test->prev == NULL);
    assert(node_under_test->count == 2);
    assert(node_under_test->value->value == NULL);
    assert(node_under_test->value->prev == NULL);
    assert(node_under_test->value->prev == NULL);
    assert(node_under_test->value->count == 1);
    free(node_under_test);
}

void test_create_node() {
    test_creating_empty_node();
    test_create_node_with_value();
}

int main(void) {
    test_create_node();
    test_push();
    test_pop();
    test_peek();
    test_push_outer();
    test_pop_outer();
}
