#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Write a function that rotates (transposes) an NxN matrix, where
 * each pixel in the image is 4 bytes. Write a function that rotates
 * the image by 90 degrees in place. */


void print_matrix(int **matrix, int matrix_size) {
    int i, j;
    for (i = 0; i < matrix_size; i++) {
        for (j = 0; j < matrix_size; j++) {
            printf("%c  ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void rotate(int ** matrix, int matrix_size, int clockwise) {
    /* Rotate a matrix 90° to the right if clockwise is true, to the left if false */
    int step, level, levels, len = matrix_size;
    char saved;

    /* in a 4x4 there would be 2 levels, in a 3x3 there would be 1 */
    levels = len / 2;

    /* loop left to right through each layer's slots, overwriting the value
     * and for the last slot replace the saved initial value. */
    for (level = 0; level < levels; level++) {
        for (step = 0; step < len - 2 * level - 1; step++) {
            /* note that y is the first index, x the second */
            saved = matrix[level][level + step];
            if (clockwise) {
                matrix[level][level + step] = matrix[len - level - step - 1][level];
                matrix[len - level - step - 1][level] = matrix[len - level - 1][len - level - step - 1];
                matrix[len - level - 1][len - level - step - 1] = matrix[level + step][len - level - 1];
                matrix[level + step][len - level - 1] = saved;
            } else {
                matrix[level][level + step] = matrix[level + step][len - level - 1];
                matrix[level + step][len - level - 1] = matrix[len - level - 1][len - level - step - 1];
                matrix[len - level - 1][len - level - step - 1] = matrix[len - level - step - 1][level];
                matrix[len - level - step - 1][level] = saved;
            }
        }
    }
}

int **init_matrix(int matrix_size) {
    /* Using int here because on 32 bit systems or larger
     * that will fit 4 bytes. Won't work on 16 bit systems though. */
    int **matrix, i;
    matrix = (int **) malloc(matrix_size * sizeof(int *));
    for (i = 0; i < matrix_size; i++) {
        matrix[i] = (int *) malloc(matrix_size * sizeof(int));
    }
    return matrix;
}

void free_matrix(int **matrix, int matrix_size) {
    /* Release the memory for a matrix */
    int i;
    for (i = 0; i < matrix_size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void populate_slots(int **matrix, int matrix_size) {
    /* Write sequential characters to each slot in the matrix */
    if (matrix_size > 8) {
        fprintf(stderr, "This program can only handle a matrix of up to a length of 8\n");
        exit(1);
    }
    matrix[0][0] = 1;
    int i, j, slot_char = '0';
    for (i = 0; i < matrix_size; i++) {
        for (j = 0; j < matrix_size; j++) {
            matrix[i][j] = slot_char;
            slot_char++;
        }
    }
}

int compare_matrix(int **first_matrix, int **second_matrix, int matrix_size) {
    /* Compare two equally large matrices. Returns 1 if they are
     * different, 0 if they are the same */
    int i, j;
    for (i = 0; i < matrix_size; i++) {
        for (j = 0; j < matrix_size; j++) {
            if (first_matrix[i][j] != second_matrix[i][j]) {
                return 1;
            }
        }
    }
    return 0;
}

void test_matrix_transpose() {
    int i, matrix_size;
    int **matrix_1, **matrix_2;

    for (matrix_size = 1; matrix_size <= 8; matrix_size++) {
        matrix_1 = init_matrix(matrix_size);
        matrix_2 = init_matrix(matrix_size);

        populate_slots(matrix_1, matrix_size);
        populate_slots(matrix_2, matrix_size);
        for (i = 0; i < 3; i++){
            rotate(matrix_1, matrix_size, 1);
        }
        rotate(matrix_2, matrix_size, 0);

        printf(
            "Checking if rotating to the right three times is "
            "the same as once to the left for size %d\n", matrix_size
        );
        assert(compare_matrix(matrix_1, matrix_2, matrix_size) == 0);

        populate_slots(matrix_1, matrix_size);
        populate_slots(matrix_2, matrix_size);
        for (i = 0; i < 3; i++){
            rotate(matrix_1, matrix_size, 0);
        }
        rotate(matrix_2, matrix_size, 1);

        printf(
            "Checking if rotating to the left three times is "
            "the same as once to the right for size %d\n", matrix_size
        );
        assert(compare_matrix(matrix_1, matrix_2, matrix_size) == 0);

        free_matrix(matrix_1, matrix_size);
        free_matrix(matrix_2, matrix_size);
    }
}

int main(void) {
    test_matrix_transpose();
    return 0;
}
