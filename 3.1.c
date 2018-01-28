#include <stdio.h>
#include <assert.h>
#include <time.h>

int HAYSTACK_SIZE = 1024;
int RUNTIME_ITERATIONS = 10000000;

/* Write a version with only one test inside the
 * loop and measure the difference in run-time. */

int kr_binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid]) {
            high = mid - 1;
        } else if (x > v[mid]) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

int new_binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high && x != v[mid]) {
        mid = (low + high) / 2;
        if (x < v[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        } 
    }
    return x == v[mid] ? mid : -1;
}

int main(void){
    int i, ret;

    /* Initialize array to search */
    int haystack[HAYSTACK_SIZE];
    for (i = 0; i < HAYSTACK_SIZE; i++) {
        haystack[i] = i;
    }

    /* Initialize the clock */
    clock_t start, end;
    double time_elapsed;

    printf("Testing k-r version\n");
    start = clock();
    for (i = 0; i < RUNTIME_ITERATIONS; i++) {
        ret = kr_binsearch(-1, haystack, HAYSTACK_SIZE);
        assert(ret == -1);
    }
    end = clock();
    time_elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf(
        "Finding non-existing value took %f seconds to execute %d times \n", 
        time_elapsed, RUNTIME_ITERATIONS
    );

    start = clock();
    for (i = 0; i < RUNTIME_ITERATIONS; i++) {
        ret = kr_binsearch(HAYSTACK_SIZE / 2, haystack, HAYSTACK_SIZE);
        assert(ret == HAYSTACK_SIZE / 2);
    }
    end = clock();
    time_elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf(
        "Finding middle value took %f seconds to execute %d times \n", 
        time_elapsed, RUNTIME_ITERATIONS
    );

    printf("Testing one if version\n");
    start = clock();
    for (i = 0; i < RUNTIME_ITERATIONS; i++) {
        ret = new_binsearch(-1, haystack, HAYSTACK_SIZE);
        assert(ret == -1);
    }
    end = clock();
    time_elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf(
        "Finding non-existing value took %f seconds to execute %d times \n", 
        time_elapsed, RUNTIME_ITERATIONS
    );

    start = clock();
    for (i = 0; i < RUNTIME_ITERATIONS; i++) {
        ret = new_binsearch(HAYSTACK_SIZE / 2, haystack, HAYSTACK_SIZE);
        assert(ret == HAYSTACK_SIZE / 2);
    }
    end = clock();
    time_elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf(
        "Finding middle value took %f seconds to execute %d times \n", 
        time_elapsed, RUNTIME_ITERATIONS
    );

    /* There's not any significant difference */
    return 0;
}

