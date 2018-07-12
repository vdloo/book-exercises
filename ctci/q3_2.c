#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Design a stack that has push and pop, but also a function that
 * can return the minimum element. All those functions should
 * operate in constant time (O(1)). */

#define push_string(push) ({ \
    for (i = 0; i < strlen(TEST_STRING); i++) { \
        push(TEST_STRING[i]); \
    } \
})

#define pop_string(pop) ({ \
    for (i = strlen(TEST_STRING) - 1; i >= 0; i--) { \
        c = pop(); \
        assert(c == TEST_STRING[i]); \
    } \
})

#define assert_store_data(push, pop) ({ \
    push_string(push); \
    pop_string(pop); \
})

const char *TEST_STRING = "How many times have you tested me? It's been a "
                          "long time, William. Longer than we thought. I "
                          "have a few questions for you. The last step's "
                          "a baseline interview to allow us to verify. "
                          "Verify what? Fidelity.\n";

typedef struct node_struct {
    char value;
    struct node_struct *prev;
} node;

node *value_node_pointer = NULL;
node *min_node_pointer = NULL;

node *create_node(char value) {
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
    return new_node;
}

node *add_left(node *node_pointer, char value) {
    /* Add a new node with the specified value on the left,
     * and return a pointer to the new head node */
    node *new_node;
    new_node = create_node(value);
    new_node->prev = node_pointer;
    return new_node;
}

node *init_or_add_left(node *node_pointer, char value) {
    if (node_pointer == NULL) {
        node_pointer = create_node(value);
    } else {
        node_pointer = add_left(node_pointer, value);
    }
    return node_pointer;
}

node *_push_once(node **node_pointer, char value) {
    *node_pointer = init_or_add_left(*node_pointer, value);
}

void push(char value) {
    _push_once(&value_node_pointer, value);
    if (min_node_pointer == NULL || min_node_pointer->value > value) {
        _push_once(&min_node_pointer, value);
    }
}

char _pop_once(node **node_pointer) {
    node *prev;
    char c;
    if (*node_pointer == NULL) {
        fprintf(
                stderr, "Can't pop from an empty stack!\n"
        );
        exit(1);
    }
    c = (*node_pointer)->value;
    prev = (*node_pointer)->prev;
    free(*node_pointer);
    *node_pointer = prev;
    return c;
}

char peek(node *node_pointer) {
    if (node_pointer == NULL) {
        fprintf(
            stderr, "Can't peek on an empty stack!\n"
        );
        exit(1);
    }
    return node_pointer->value;
}

char pop() {
    char c;
    c = _pop_once(&value_node_pointer);
    if (peek(min_node_pointer) == c) {
        _pop_once(&min_node_pointer);
    }
    return c;
}

char min() {
    return peek(min_node_pointer);
}

int main(void) {
    int i;
    char c;
    printf("Verifying stack can store data\n");
    assert_store_data(push, pop);
    printf("Asserting min char in string is newline\n");
    push_string(push);
    assert(min() == '\n');
    pop_string(pop);
    push('z');
    printf("Asserting min char on 1 elem stack is correct\n");
    assert(min() == 'z');
    return 0;
}
