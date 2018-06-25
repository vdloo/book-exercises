#include <stdio.h>
#include <stdlib.h>

/* Write an algorithm such that if an element in an MxN matrix is 0,
 * the entire row and column are set to 0. */


/* 
$ gcc q1_8.c && ./a.out
0  0  0  0  0  0  0  0  0  0
;  <  =  0  ?  @  A  B  0  D
0  0  0  0  0  0  0  0  0  0
O  P  Q  0  S  T  U  V  0  X
Y  Z  [  0  ]  ^  _  `  0  b
c  d  e  0  g  h  i  j  0  l

$ gcc q1_8.c && ./a.out
0  2  0  4  5  6  7  8  9  :
0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0
0  P  0  R  S  T  U  V  W  X
0  Z  0  \  ]  ^  _  `  a  b
0  d  0  f  g  h  i  j  k  l  
*/


void print_matrix(int **matrix, int matrix_w, int matrix_h) {
    int i, j;
    for (i = 0; i < matrix_h; i++) {
        for (j = 0; j < matrix_w; j++) {
            printf("%c  ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void zero_row_and_col(int **matrix, int matrix_w, int matrix_h, int s_h, int s_w) {
    /* Zero the entire column and row for each element where a 0 appears
     * Takes as arguments the matrix, the width and height of that matrix,
     * and two state variables h and w for keeping track at which coordinates
     * a zero is detected on the stack. There's no explicit list of coordinates
     * that we need to zero out, but recursion is used instead to achieve the same. */
    int i, j, h, k, broke = 0;
    for (i = s_h; i < matrix_h; i++) {
        for (j = s_w; j < matrix_w; j++) {
            if (matrix[i][j] == '0') {
                zero_row_and_col(matrix, matrix_w, matrix_h, i, j + 1);
                broke = 1;
                break;
            }
        }
        s_w = 0;
        if (broke) {
            break;
        }
    }
    if (broke) {
        for (h = 0; h < matrix_w; h++) {
            matrix[i][h] = '0';
        }
        for (k = 0; k < matrix_h; k++) {
            matrix[k][j] = '0';
        }
    }
}

int **init_matrix(int matrix_w, int matrix_h) {
    int **matrix, i;
    matrix = (int **) malloc(matrix_h * sizeof(int *));
    for (i = 0; i < matrix_h; i++) {
        matrix[i] = (int *) malloc(matrix_w * sizeof(int));
    }
    return matrix;
}

void free_matrix(int **matrix, int matrix_h) {
    /* Release the memory for a matrix */
    int i;
    for (i = 0; i < matrix_h; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void populate_slots(int **matrix, int matrix_w, int matrix_h) {
    /* Write sequential characters to each slot in the matrix */
    if (matrix_w * matrix_h > 63) {
        fprintf(stderr, "This program can only handle a matrix with up to 63 elements\n");
        exit(1);
    }
    int i, j, slot_char = '1';
    srand(time(NULL));
    for (i = 0; i < matrix_h; i++) {
        for (j = 0; j < matrix_w; j++) {
            if (rand() % 20 == 0) {
                /* 5% chance of placing a '0' instead of the sequential char */
                matrix[i][j] = '0';
            } else {
                matrix[i][j] = slot_char;
            }
            slot_char++;
        }
    }
}

void matrix_zero_col_and_row() {
    int i, matrix_w = 10, matrix_h = 6;
    int **matrix;
    matrix = init_matrix(matrix_w, matrix_h);
    populate_slots(matrix, matrix_w, matrix_h);
    zero_row_and_col(matrix, matrix_w, matrix_h, 0, 0);
    print_matrix(matrix, matrix_w, matrix_h);
    free_matrix(matrix, matrix_h);
}

int main(void) {
    matrix_zero_col_and_row();
    return 0;
}
