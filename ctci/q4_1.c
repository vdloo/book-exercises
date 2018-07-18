#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define GRID_SIZE 8

/* Given a directed graph, design an algorithm to find out whether there is
 * a route between nodes (Depth-First-Search, Breadth-First-Search). */

typedef struct node_struct {
    int id;
    char state;
    struct node_struct *next;
    struct node_struct *neighbours;
    struct node_struct *value;
} node;

node *grid = NULL;

void push(node **next, node *value, int id) {
    node * new_node = NULL;
    new_node = malloc(sizeof(node));
    if (new_node == NULL) {
        fprintf(
            stderr, "Failed to allocate memory for "
                    "new node in linked list\n"
        );
        exit(1);
    }
    new_node->next = *next;
    if (id == -1) {
        if (*next == NULL) {
            new_node->id = 0;
        } else {
            new_node->id = (*next)->id + 1;
        }
    } else {
        new_node->id = id;
    }
    new_node->neighbours = NULL;
    new_node->value = value;
    new_node->state = 'x';
    *next = new_node;
}

node *pop(node **node_pointer) {
    node *value;
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

void flush_forward_to_backward(node **queue_forward, node **queue_backward) {
    while (*queue_forward != NULL) {
        push(queue_backward, pop(queue_forward), -1);
    }
}

void queue_add(node **queue_forward, node **queue_backward, node *value) {
    flush_forward_to_backward(queue_backward, queue_forward);
    push(queue_forward, value, -1);
}

node *queue_remove(node **queue_forward, node **queue_backward) {
    flush_forward_to_backward(queue_forward, queue_backward);
    return pop(queue_backward);
}

void init_grid() {
    grid = NULL;
    int i;
    for (i = 0; i < GRID_SIZE * GRID_SIZE; i++) {
        push(&grid, NULL, -1);
    }
}

node *get_row(int row_nr) {
    int i;
    node *node_pointer = grid;
    node *row_list = NULL;
    if (row_nr >= GRID_SIZE) {
        fprintf(
            stderr, "Can't get row %d, this grid only has "
                    "%d!\n", row_nr, (GRID_SIZE - 1)
        );
        exit(1);
    }
    for (i = 0; i < GRID_SIZE * GRID_SIZE; i++) {
        if (i >= row_nr * GRID_SIZE && i < (row_nr * GRID_SIZE) + GRID_SIZE) {
            push(&row_list, node_pointer, node_pointer->id);
        }
        node_pointer = node_pointer->next;
    }

    return row_list;
}

node *get_column(int col_nr) {
    int i;
    node *node_pointer = grid;
    node *col_list = NULL;
    if (col_nr >= GRID_SIZE) {
        fprintf(
            stderr, "Can't get column %d, this grid only has "
                    "%d!\n", col_nr, (GRID_SIZE - 1)
        );
        exit(1);
    }
    for (i = 0; i < GRID_SIZE * GRID_SIZE; i++) {
        if (i % GRID_SIZE == col_nr) {
            push(&col_list, node_pointer, node_pointer->id);
        }
        node_pointer = node_pointer->next;
    }

    return col_list;
}

void create_edge(node *from_node, node *to_node) {
    if (from_node == NULL) {
        fprintf(
                stderr, "Can't create edge from a node that is NULL!\n"
        );
        exit(1);
    }
    if (to_node == NULL) {
        fprintf(
                stderr, "Can't create edge to a node that is NULL!\n"
        );
        exit(1);
    }
    push(&(from_node->neighbours), to_node, -1);
}

void connect_list(node *node_pointer) {
    while (node_pointer != NULL) {
        if (node_pointer->next != NULL) {
            create_edge(node_pointer->value, node_pointer->next->value);
            create_edge(node_pointer->next->value, node_pointer->value);
        }
        node_pointer = node_pointer->next;
    }
}

void free_list(node *node_pointer) {
    node *tmp;
    while (node_pointer != NULL) {
        tmp = node_pointer;
        node_pointer = node_pointer->next;
        free(tmp);
    }
    node_pointer = NULL;
}

void connect_grid() {
    int i;
    node *node_pointer;
    for (i = 0; i < GRID_SIZE; i++) {
        node_pointer = get_row(i);
        connect_list(node_pointer);
        free_list(node_pointer);
        node_pointer = get_column(i);
        connect_list(node_pointer);
        free_list(node_pointer);
    }
    assert(grid->neighbours != NULL);
}

int is_neigh(node *from_node, node *to_node) {
    /* Return 1 if the the from node has an edge to the to node, 0 if not */
    node *node_pointer = from_node->neighbours;
    while (node_pointer != NULL) {
        if (node_pointer->value == to_node) {
            return 1;
        }
        node_pointer = node_pointer->next;
    }
    return 0;
}

void print_grid() {
    int i, j;
    int left, right;
    node *node_pointer = grid;
    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 0; j < GRID_SIZE; j++) {
            left = ' ';
            right = ' ';
            if (node_pointer->next != NULL) {
                left = is_neigh(node_pointer->next, node_pointer) ? '<' : ' ';
                right = is_neigh(node_pointer, node_pointer->next) ? '>' : ' ';
            }
            printf(
                "%s%c\x1B[0m %c%c ",
                node_pointer->state == 'p' ? "\x1B[31m" :
                node_pointer->state == 'd' || node_pointer->state == 's' ?
                "\x1B[33m" : "\x1B[34m",
                node_pointer->state,
                left, right
            );
            node_pointer = node_pointer->next;
        }
        printf("\n");
        /* for simplicity in visualization let's say all vertical nodes
         * are connected both ways */
        if (i + 1 != GRID_SIZE) {
            for (j = 0; j < GRID_SIZE; j++) {
                printf("|    ");
            }
            printf("\n");
        }
    }
}

void randomly_sever() {
    /* randomly sever connections between nodes. */
    node *node_pointer = grid;
    int i;
    for (i = 0; i < GRID_SIZE * GRID_SIZE; i++) {
        /* 33.3% chance of removing all neighbours from a node */
        if (rand() % 3 == 0) {
            free_list(node_pointer->neighbours);
            node_pointer->neighbours = NULL;
        }
        node_pointer = node_pointer->next;
    }
}

int find_path_depth_first_iter(node *from_node, node *to_node) {
    if (from_node->neighbours == NULL || to_node->neighbours == NULL) {
        /* There won't be a path if there aren't any neighbours */
        return 0;
    }
    if (from_node->state != 'v') {
        from_node->state = 'v';  /* v for visited */
    }
    node *node_pointer = from_node->neighbours;
    while (node_pointer != NULL) {
        if (node_pointer->value == to_node) {
            return 1;
        }
        if (node_pointer->value->state != 'v') {
            if (find_path_depth_first_iter(node_pointer->value, to_node) == 1) {
                node_pointer->value->state = 'p';
                return 1;
            };
        }
        node_pointer = node_pointer->next;
    }
    return 0;
}

int find_path_depth_first(node *from_node, node *to_node) {
    /* Find a path from the top left to the bottom right using DFS.
     * Returns 1 when a path if found 0 if not */
    int i;
    i = find_path_depth_first_iter(from_node, to_node);
    from_node->state = 's';  /* s for source */
    to_node->state = 'd';  /* d for destination */
    return i;
}

int find_path_breadth_first_iter(
        node **queue_forward, node **queue_backward, node *to_node
) {
    node *node_pointer, *neighbour;
    while (*queue_forward != NULL || *queue_backward != NULL) {
        node_pointer = queue_remove(queue_forward, queue_backward);
        neighbour = node_pointer->neighbours;
        while (neighbour != NULL) {
            if (neighbour->value == to_node) {
                return 1;
            }
            if (neighbour->value->state != 'p') {
                neighbour->value->state = 'p';
                queue_add(queue_forward, queue_backward, neighbour->value);
            }
            neighbour = neighbour->next;
        }
    }
    return 0;
}

int find_path_breadth_first(node *from_node, node *to_node) {
    /* Find a path from the top left to the bottom right using BFS.
     * Returns 1 when a path if found 0 if not */
    int i;
    node *queue_forward = NULL;
    node *queue_backward = NULL;
    queue_add(&queue_forward, &queue_backward, from_node);
    from_node->state = 'p';
    i = find_path_breadth_first_iter(&queue_forward, &queue_backward, to_node);
    from_node->state = 's';  /* s for source */
    to_node->state = 'd';  /* d for destination */
    return i;
}

node *get_last(node *node_pointer) {
    while (node_pointer->next != NULL) {
        node_pointer = node_pointer->next;
    }
    return node_pointer;
}

node *get_nth(node *node_pointer, int n) {
    while (node_pointer->next != NULL && n > 0) {
        node_pointer = node_pointer->next;
        n--;
    }
    return node_pointer;
}

void test_specified_row(int row_nr) {
    node *node_pointer, *tmp;
    int i;
    node_pointer = get_row(row_nr);
    i = 0;
    while (node_pointer != NULL) {
        assert(node_pointer->id == (GRID_SIZE * GRID_SIZE) - ((row_nr + 1) * GRID_SIZE) + i);
        tmp = node_pointer;
        node_pointer = node_pointer->next;
        free(tmp);
        i++;
    }
}

void test_specified_col(int col_nr) {
    node *node_pointer, *tmp;
    int i;
    node_pointer = get_column(col_nr);
    i = 0;
    while (node_pointer != NULL) {
        assert(node_pointer->id == GRID_SIZE - col_nr - 1 + (i * GRID_SIZE));
        tmp = node_pointer;
        node_pointer = node_pointer->next;
        free(tmp);
        i++;
    }
}

void test_get_row() {
    printf("Testing get_row works as intended\n");
    int i;
    for (i = 0; i < GRID_SIZE; i++) {
        test_specified_row(i);
    }
}

void test_get_column() {
    printf("Testing get_col works as intended\n");
    int i;
    for (i = 0; i < GRID_SIZE; i++) {
        test_specified_col(i);
    }
}

void test_create_edge() {
    printf("Testing create edge\n");
    node *node_under_test = NULL;
    push(&node_under_test, NULL, -1);
    push(&node_under_test, NULL, -1);
    assert(node_under_test->neighbours == NULL);
    assert(node_under_test->next->neighbours == NULL);
    create_edge(node_under_test, node_under_test->next);
    assert(node_under_test->neighbours != NULL);
    assert(node_under_test->neighbours->value == node_under_test->next);
    assert(node_under_test->next->neighbours == NULL);
    create_edge(node_under_test->next, node_under_test);
    assert(node_under_test->neighbours != NULL);
    assert(node_under_test->neighbours->value == node_under_test->next);
    assert(node_under_test->next->neighbours != NULL);
    assert(node_under_test->next->neighbours->value == node_under_test);
    free(node_under_test->next);
    free(node_under_test);
}

void test_grid_connected() {
    int i, c;
    node *node_pointer = grid, *tmp;
    for (i = 0; i < GRID_SIZE * GRID_SIZE; i++) {
        c = 0;
        tmp = node_pointer->neighbours;
        while (tmp != NULL) {
            c++;
            tmp = tmp->next;
        }
        switch (i) {
            case 0:
                assert(c == 2);
                break;
            case 1:
                assert(c == 3);
                break;
            case GRID_SIZE - 1:
                assert(c == 2);
                break;
            case GRID_SIZE:
                assert(c == 3);
                break;
            case GRID_SIZE + 1:
                assert(c == 4);
                break;
            case GRID_SIZE * GRID_SIZE:
                assert(c == 2);
                break;
        }
        node_pointer = node_pointer->next;
    }
}

void test_is_neigh() {
    printf("Testing is neighbour\n");
    node *node_under_test = NULL;
    push(&node_under_test, NULL, -1);
    push(&node_under_test, NULL, -1);
    assert(is_neigh(node_under_test, node_under_test->next) == 0);
    assert(is_neigh(node_under_test->next, node_under_test) == 0);
    create_edge(node_under_test, node_under_test->next);
    assert(is_neigh(node_under_test, node_under_test->next) == 1);
    assert(is_neigh(node_under_test->next, node_under_test) == 0);
    create_edge(node_under_test->next, node_under_test);
    assert(is_neigh(node_under_test, node_under_test->next) == 1);
    assert(is_neigh(node_under_test->next, node_under_test) == 1);
    free(node_under_test->next);
    free(node_under_test);
}

void setup_maze() {
    init_grid();
    connect_grid();
}

void test_depth_first(int sever, int last) {
    int ret;
    setup_maze();
    if (sever) {
        randomly_sever();
    }
    node *first_node = grid, *target_node;
    if (last) {
        target_node = get_last(grid);
    } else {
        target_node = get_nth(
            grid, ((GRID_SIZE * GRID_SIZE) / 2) - GRID_SIZE / 3
        );
    }
    ret = find_path_depth_first(first_node, target_node);
    if (sever) {
        printf(
            "Depth first search on randomized directed graph looks like:\n"
        );
    } else {
        printf("Depth first search on pristine grid looks like:\n");
        /* in case of the pristine grid there should always be a path */
        assert(ret == 1);
    }
    print_grid();
}

void test_breadth_first(int sever, int last) {
    int ret;
    setup_maze();
    if (sever) {
        randomly_sever();
    }
    node *first_node = grid, *target_node;
    if (last) {
        target_node = get_last(grid);
    } else {
        target_node = get_nth(
            grid, ((GRID_SIZE * GRID_SIZE) / 2) - GRID_SIZE / 3
        );
    }
    ret = find_path_breadth_first(first_node, target_node);
    if (sever) {
        printf(
            "Breadth first search on randomized directed graph looks like:\n"
        );
    } else {
        printf("Breadth first search on pristine grid looks like:\n");
        /* in case of the pristine grid there should always be a path */
        assert(ret == 1);
    }
    print_grid();
}

void unit_tests() {
    setup_maze();
    test_get_row();
    test_get_column();
    test_create_edge();
    test_grid_connected();
    test_is_neigh();
    free_list(grid);
}

int main(void) {
    srand(time(NULL));
    unit_tests();
    test_depth_first(0, 0);
    test_depth_first(0, 1);
    test_depth_first(1, 0);
    test_depth_first(1, 1);
    test_breadth_first(0, 0);
    test_breadth_first(0, 1);
    test_breadth_first(1, 0);
    test_breadth_first(1, 1);
    exit(0);
}
