#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* There's a queue with two types of values. There are three
 * functions to get the next value from the queue. remove_dog,
 * remove_cat and remove_any. Use linked list(s) */

typedef struct node_struct {
    char value;
    int id;
    struct node_struct *next;
} node;

node *dog_stack_forward = NULL, *cat_stack_forward = NULL;
node *dog_stack_backward = NULL, *cat_stack_backward = NULL;

void push(node **next, char value, int id) {
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
    new_node->id = id;
    new_node->next = *next;
    *next = new_node;
}

char pop(node **node_pointer) {
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

void flush_forward_to_backward(node **queue_forward, node **queue_backward) {
    int i, id;
    while (*queue_forward != NULL) {
        i++;
        id = (*queue_forward)->id;
        push(queue_backward, pop(queue_forward), id);
    }
}

void add(char c, int dog) {
    /* 1 if dog, 0 if cat */
    int id = 0;
    flush_forward_to_backward(&dog_stack_backward, &dog_stack_forward);
    flush_forward_to_backward(&cat_stack_backward, &cat_stack_forward);
    if (cat_stack_forward) {
        id = cat_stack_forward->id > id ? cat_stack_forward->id : id;
    }
    if (dog_stack_forward) {
        id = dog_stack_forward->id > id ? dog_stack_forward->id : id;
    }
    assert(dog_stack_backward == NULL);
    assert(cat_stack_backward == NULL);
    push(dog ? &dog_stack_forward : &cat_stack_forward, c, id + 1);
}

void add_dog(char c) {
    add(c, 1);
}

void add_cat(char c) {
    add(c, 0);
}

char remove_dog() {
    flush_forward_to_backward(&dog_stack_forward, &dog_stack_backward);
    if (dog_stack_backward == NULL) {
        fprintf(
            stderr, "You can not pop from an empty stack!\n"
        );
        exit(1);
    }
    return pop(&dog_stack_backward);
}

char remove_cat() {
    flush_forward_to_backward(&cat_stack_forward, &cat_stack_backward);
    if (cat_stack_backward == NULL) {
        fprintf(
            stderr, "You can not pop from an empty stack!\n"
        );
        exit(1);
    }
    return pop(&cat_stack_backward);
}

char remove_any() {
    flush_forward_to_backward(&dog_stack_forward, &dog_stack_backward);
    flush_forward_to_backward(&cat_stack_forward, &cat_stack_backward);
    if (cat_stack_backward == NULL) {
        if (dog_stack_backward == NULL) {
            fprintf(
                stderr, "You can not pop from an empty stack!\n"
            );
            exit(1);
        } else {
            return remove_dog();
        }
    } else {
        if (dog_stack_backward == NULL) {
            return remove_cat();
        }
    }
    if (dog_stack_backward->id < cat_stack_backward->id) {
        return remove_dog();
    } else {
        return remove_cat();
    }

}

void test_stack() {
    printf("Asserting animal shelter is working as intended\n");
    add_dog('a');
    add_cat('b');
    add_dog('c');
    add_cat('d');
    add_cat('e');
    assert(remove_cat() == 'b');
    assert(remove_dog() == 'a');
    assert(remove_any() == 'c');
    assert(remove_any() == 'd');
    assert(remove_any() == 'e');
}

int main(void) {
    test_stack();
    exit(0);
}
