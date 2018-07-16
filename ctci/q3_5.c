#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Sort a stack such that the smallest items are at the top. Use
 * one additional temporary array. The stack supports: push, pop,
 * peek and is_empty */

typedef struct node_struct {
    char value;
    struct node_struct *next;
} node;

node *temp_stack = NULL, *stack = NULL;

void _push(node **next, char value) {
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
    new_node->next = *next;
    *next = new_node;
}

char _pop(node **node_pointer) {
    char value;
    node *tmp;
    if (node_pointer == NULL) {
        fprintf(
            stderr, "You can not pop from an empty stack!\n"
        );
        exit(1);
    }
    value = (*node_pointer)->value;
    tmp = *node_pointer;
    *node_pointer = (*node_pointer)->next;
    free(tmp);
    return value;
}

char pop() {
    if (stack == NULL) {
        fprintf(
            stderr, "You can not pop from an empty stack!\n"
        );
        exit(1);
    }
    return _pop(&stack);
}

char peek() {
    return stack->value;
}

void push(char value) {
    while (stack != NULL && value >= peek(stack)) {
        _push(&temp_stack, _pop(&stack));
    }
    _push(&stack, value);
    while (temp_stack != NULL) {
        _push(&stack, _pop(&temp_stack));
    }
}

int is_empty() {
    /* Return 1 if empty, 0 if not */
    return stack == NULL;
}

void test_stack() {
    printf("Asserting sorted stack is working as intended\n");
    assert(is_empty() == 1);
    push('b');
    assert(is_empty() == 0);
    push('a');
    push('c');
    push('e');
    push('d');
    assert(temp_stack == NULL);
    assert(pop() == 'a');
    assert(pop() == 'b');
    assert(pop() == 'c');
    assert(pop() == 'd');
    assert(is_empty() == 0);
    assert(pop() == 'e');
    assert(temp_stack == NULL);
    assert(is_empty() == 1);
}

int main(void) {
    test_stack();
    exit(0);
}
