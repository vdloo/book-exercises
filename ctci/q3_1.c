#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/* Use a single (one dimension) array to create 3 stacks */

/*
$ gcc q3_1.c -g && ./a.out
Verifying stack 1 can store data
Verifying stack 2 can store data
Verifying stack 3 can store data
Verifying all stacks can be pushed to interchangeably
Verifying we can completely fill up and empty out stack 1
Verifying no null-bytes are found if this stack occupies all mem
Verifying the values we pop off are the same we put in
Verifying we can completely fill up and empty out stack 2
Verifying no null-bytes are found if this stack occupies all mem
Verifying the values we pop off are the same we put in
Verifying we can completely fill up and empty out stack 3
Verifying no null-bytes are found if this stack occupies all mem
Verifying the values we pop off are the same we put in
Verifying stack didn't leak any memory
*/


#define BUFFER_SIZE 256
#define WRITABLE_SIZE 252
unsigned char BUFFER[BUFFER_SIZE];
const char *TEST_STRING = "How many times have you tested me? It's been a "
                          "long time, William. Longer than we thought. I "
                          "have a few questions for you. The last step's "
                          "a baseline interview to allow us to verify. "
                          "Verify what? Fidelity.";

#define assert_store_data(push, pop) ({ \
    for (i = 0; i < strlen(TEST_STRING); i++) { \
        push(TEST_STRING[i]); \
    } \
    for (i = strlen(TEST_STRING) - 1; i >= 0; i--) { \
        c = pop(); \
        assert(c == TEST_STRING[i]); \
    } \
})

#define assert_fill_stack(push, pop) ({ \
    for (i = 0; i < WRITABLE_SIZE - 2; i++) { \
        push('a'); \
    } \
    printf( \
        "Verifying no null-bytes are found if this stack occupies all mem\n" \
    ); \
    assert(count_empty_addresses() == 2); \
    printf("Verifying the values we pop off are the same we put in\n"); \
    for (i = WRITABLE_SIZE - 2 - 1; i >= 0; i--) { \
        assert('a' == pop()); \
    } \
})

/* The first 4 bytes store the start address of the second stack
 * and the current length of each stack. This is later used to
 * determine where to move the second stack to when there is a
 * collision. By moving it so that for both stack 1 and 3 the
 * most free sequential addresses will be available we can
 * amortize the heavy operation of moving the entire second
 * stack and keep the chance of having to do it to a minimum.
 * There's a couple bytes we can't address, that's because of
 * how detecting where to move the second stack to works. Those
 * couple of bytes grow as the buffer grows. Those could be
 * reclaimed but that would come at the cost of complicating
 * the code a bunch or making the decision of where to move
 * the second stack to less optimal. */
int get_stack_1_start_address() {
    return 4;
}

int get_stack_2_start_address() {
    return BUFFER[0];
}

int get_stack_3_start_address() {
    return BUFFER_SIZE - 1;
}

void set_stack_2_start_address(int address) {
    BUFFER[0] = address;
}

int get_stack_1_length() {
    return BUFFER[1];
}

void increment_stack_1_length() {
    BUFFER[1]++;
}

void decrement_stack_1_length() {
    BUFFER[1]--;
}

int get_stack_2_length() {
    return BUFFER[2];
}

void increment_stack_2_length() {
    BUFFER[2]++;
}

void decrement_stack_2_length() {
    BUFFER[2]--;
}

int get_stack_3_length() {
    return BUFFER[3];
}

void increment_stack_3_length() {
    BUFFER[3]++;
}

void decrement_stack_3_length() {
    BUFFER[3]--;
}

void init_stack_meta() {
    /* Setting the start of stack 2 to two thirds into the array */
    set_stack_2_start_address((BUFFER_SIZE * 2) / 3);
    /* Initializing all stack lengths to 0 */
    BUFFER[1], BUFFER[2], BUFFER[3] = 0;
};

void move_stack_2_forward(int offset) {
    int i, stack_2_end = get_stack_2_start_address() + get_stack_2_length();
    for (i = stack_2_end; i >= get_stack_2_start_address(); i--) {
        BUFFER[i + offset] = BUFFER[i];
        BUFFER[i] = '\0';
    }
    set_stack_2_start_address(get_stack_2_start_address() + offset);
}

void move_stack_2_backward(int offset) {
    int i, stack_2_end = get_stack_2_start_address() + get_stack_2_length();
    int c = 0;
    for (i = get_stack_2_start_address(); i < stack_2_end; i++) {
        BUFFER[i + offset] = BUFFER[i];
        BUFFER[i] = '\0';
    }
    set_stack_2_start_address(get_stack_2_start_address() + offset);
}

void make_space() {
    /* move the second stack to make space for the new pushed element */
    int most_dist_address, new_stack_2_start_address, offset;
    int stack_3_end = get_stack_3_start_address() - get_stack_3_length();
    int stack_1_end = get_stack_1_start_address() + get_stack_1_length();
    if (stack_3_end - stack_1_end <= get_stack_2_length() + 1) {
        fprintf(
            stderr, "Out of memory in the buffer!\n"
        );
        exit(1);
    }
    most_dist_address = ((stack_3_end + stack_1_end) / 2);
    new_stack_2_start_address = most_dist_address - (get_stack_2_length() / 2);
    offset = new_stack_2_start_address - get_stack_2_start_address();
    if (offset > 0) {
        move_stack_2_forward(offset);
    } else {
        move_stack_2_backward(offset);
    }

}

void push_stack_1(char c) {
    int new_address = get_stack_1_start_address() + get_stack_1_length();
    if (new_address == get_stack_2_start_address()) {
        /* colliding with stack 2, trying to make room before proceeding */
        make_space();
        new_address = get_stack_1_start_address() + get_stack_1_length();
    }
    BUFFER[new_address] = c;
    increment_stack_1_length();
}

char pop_stack_1() {
    int c;
    if (get_stack_1_length() == 0) {
        fprintf(
            stderr, "Can't pop from stack 1, it is empty!\n"
        );
        exit(1);
    }
    decrement_stack_1_length();
    c = BUFFER[get_stack_1_start_address() + get_stack_1_length()];
    BUFFER[get_stack_1_start_address() + get_stack_1_length()] = '\0';
    return c;
}

void push_stack_2(char c) {
    int new_address = get_stack_2_start_address() + get_stack_2_length();
    if (new_address == (get_stack_3_start_address() - get_stack_3_length())) {
        /* colliding with stack 3, trying to make room before proceeding */
        make_space();
        new_address = get_stack_2_start_address() + get_stack_2_length();
    }
    BUFFER[new_address] = c;
    increment_stack_2_length();
}

char pop_stack_2() {
    int c;
    if (get_stack_2_length() == 0) {
        fprintf(
            stderr, "Can't pop from stack 2, it is empty!\n"
        );
        exit(1);
    }
    decrement_stack_2_length();
    c = BUFFER[get_stack_2_start_address() + get_stack_2_length()];
    BUFFER[get_stack_2_start_address() + get_stack_2_length()] = '\0';
    return c;
}

void push_stack_3(char c) {
    int new_address = get_stack_3_start_address() - get_stack_3_length();
    if (new_address == (get_stack_2_start_address() + get_stack_2_length())) {
        /* colliding with stack 2, trying to make room before proceeding */
        make_space();
        new_address = get_stack_3_start_address() - get_stack_3_length();
    }
    BUFFER[new_address] = c;
    increment_stack_3_length();
}

char pop_stack_3() {
    int c;
    if (get_stack_3_length() == 0) {
        fprintf(
            stderr, "Can't pop from stack 3, it is empty!\n"
        );
        exit(1);
    }
    decrement_stack_3_length();
    c = BUFFER[get_stack_3_start_address() - get_stack_3_length()];
    BUFFER[get_stack_3_start_address() - get_stack_3_length()] = '\0';
    return c;
}

int count_empty_addresses() {
    int i, count = 0;
    for (i = get_stack_1_start_address(); i < BUFFER_SIZE; i++) {
        if (BUFFER[i] == '\0') {
            count++;
        }
    }
    return count;
}

void test_push_interchangeably() {
    int i;
    char c;

    for (i = 0; i < strlen(TEST_STRING); i++) {
        switch (i % 3) {
            case 0:
                push_stack_1(TEST_STRING[i]);
                break;
            case 1:
                push_stack_2(TEST_STRING[i]);
                break;
            case 2:
                push_stack_3(TEST_STRING[i]);
                break;
        }
    }

    for (i = strlen(TEST_STRING) - 1; i >= 0; i--) {
        switch (i % 3) {
            case 0:
                c = pop_stack_1();
                break;
            case 1:
                c = pop_stack_2();
                break;
            case 2:
                c = pop_stack_3();
                break;
        }
        assert(c == TEST_STRING[i]);
    }
}

void test_single_array_stacks() {
    int i;
    char c;

    printf("Verifying stack 1 can store data\n");
    assert_store_data(push_stack_1, pop_stack_1);
    printf("Verifying stack 2 can store data\n");
    assert_store_data(push_stack_2, pop_stack_2);
    printf("Verifying stack 3 can store data\n");
    assert_store_data(push_stack_3, pop_stack_3);
    printf("Verifying all stacks can be pushed to interchangeably\n");
    test_push_interchangeably();

    printf("Verifying we can completely fill up and empty out stack 1\n");
    assert_fill_stack(push_stack_1, pop_stack_1);
    printf("Verifying we can completely fill up and empty out stack 2\n");
    assert_fill_stack(push_stack_2, pop_stack_2);
    printf("Verifying we can completely fill up and empty out stack 3\n");
    assert_fill_stack(push_stack_3, pop_stack_3);
    printf("Verifying stack didn't leak any memory\n");
    assert(count_empty_addresses() == WRITABLE_SIZE);
}

int main(void) {
    init_stack_meta();
    test_single_array_stacks();
    return 0;
}
