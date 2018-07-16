#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Implement a queue using two stacks. Should
 * support: queue_add, queue_remove, queue_peek and queue_is_empty */

typedef struct node_struct {
    char value;
    struct node_struct *next;
} node;

node *queue_forward = NULL, *queue_backward = NULL;

void push(node **next, char value) {
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

char pop(node **node_pointer) {
    char value;
    node *tmp;
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

void queue_add(char value) {
    push(&queue_forward, value);
}

void flush_forward_to_backward() {
    while (queue_forward != NULL) {
        push(&queue_backward, pop(&queue_forward));
    }
}

char queue_remove() {
    flush_forward_to_backward();
    return pop(&queue_backward);
}

char queue_peek() {
    flush_forward_to_backward();
    return queue_backward->value;
}

int queue_is_empty() {
    /* Return 1 if empty, 0 if not */
    return queue_forward == NULL && queue_backward == NULL;
}

void test_queue() {
    printf("Asserting queue is working as intended\n");
    int i;
    char c;
    assert(queue_is_empty() == 1);
    for (i = 0; i < 100; i++) {
        queue_add(i);
    }
    assert(queue_is_empty() == 0);
    for (i = 0; i < 100; i++) {
        c = queue_peek();
        assert(c == i);
        c = queue_remove();
    }
    assert(c == 99);
    assert(queue_is_empty() == 1);
}

void test_stack() {
    int i;
    char c;
    printf("Asserting stack is working as intended\n");
    node *node_pointer = NULL;
    for (i = 0; i < 100; i++) {
        push(&node_pointer, i);
    }
    assert(node_pointer != NULL);
    for (i = 0; i < 100; i++) {
        c = pop(&node_pointer);
        assert(c == 100 - i - 1);
    }
    assert(node_pointer == NULL);
}

int main(void) {
    test_stack();
    test_queue();
    exit(0);
}
