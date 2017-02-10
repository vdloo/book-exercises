#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#define BENCH_MAX 10000000

/* Note: this statement expression macro is not standard C99 but a GCC 
 * extension. You can write it out by hand but for the sake of brevity 
 * this bit of metaprogramming here will allow for some nice abstraction */
#define benchmark_function(func) ({ \
    double micro_seconds; \
    float seconds; \
    clock_t start, end; \
    unsigned i; \
    start = clock(); \
    for (i = 0; i < BENCH_MAX; i++) { \
        func(i); \
    } \
    end = clock(); \
    micro_seconds = end - start; \
    seconds = micro_seconds / 1000000; \
    return seconds; \
})

/* In a two's complements system (x &= x -1) always deletes the rightmost 
 * 1-bit of x because either the 1-bit becomes 1 because the 2-bit used to be 1
 * and the 1-bit was 0, or the 1-bit becomes 0 because it was 1. In both those 
 * cases a binary AND will set the 1-bit to 0. This wouldn't work in a one's 
 * complement system because you can represent 0 both as a positive and 
 * negative number (all zeroes and all ones), in a two's complement system 
 * you can only represent 0 as all zeroes. All ones would be -1. */

/* Test 1 -> 1-bit zero to one
 * | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | 
 * |128| 64| 32| 16| 8 | 4 | 2 | 1 |
 * | 1 | 0 | 1 | 1 | 1 | 0 | 1 | 0 |
 *  186 = 128 + 32 + 16 + 8 + 2
 * | 1 | 0 | 1 | 1 | 1 | 0 | 0 | 1 |
 *  185 = 128 + 32 + 16 + 8 + 1
 *  186 after binary AND with 185 becomes
 * | 1 | 0 | 1 | 1 | 1 | 0 | 0 | 0 |
 *  184 = 128 + 32 + 16 + 8 */

/* Test 2 -> 1-bit one to zero
 * | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | 
 * |128| 64| 32| 16| 8 | 4 | 2 | 1 |
 * | 1 | 0 | 1 | 1 | 1 | 0 | 0 | 1 |
 *  185 = 128 + 32 + 16 + 8 + 1
 * | 1 | 0 | 1 | 1 | 1 | 0 | 0 | 0 |
 *  184 = 128 + 32 + 16 + 8
 *  185 after binary AND with 184 becomes
 * | 1 | 0 | 1 | 1 | 1 | 0 | 0 | 0 |
 *  184 = 128 + 32 + 16 + 8 */

unsigned del_right_most_bit(unsigned int x)
{
    x &= x - 1;
    return x;
}

int bitcount(unsigned x)
{
    int b;
    for (b = 0; x != 0; x>>= 1) {
        if (x & 01) {
            b++;
        }
    }
    return b;
}

unsigned int fast_bitcount(unsigned x)
{
    int b;
    /* this works because it sets all one bits to 0 from right to left,
     * finally when the last one bit has been set to 0, x will be zero */
    for (b = 0; x != 0; x &= x - 1) {
        b++;
    }
    return b;
}

void test_del_right_most_bit()
{
    unsigned int ret, x;

    x = 186;
    ret = del_right_most_bit(x);
    printf(
        "The result of setting the right " \
        "most bit to 0 of of %d is %d\n",
        x, ret
    );
    assert(ret == 184);

    x = 185;
    ret = del_right_most_bit(x);
    printf(
        "The result of setting the right " \
        "most bit to 0 of of %d is %d\n",
        x, ret
    );
    assert(ret == 184);
}

void test_bitcounts()
{
    int i;
    printf("Checking if both bitcount " \
            "functions return the same " \
            "results\n");
    for (i = 0; i < BENCH_MAX; i++) {
        assert(bitcount(i) == fast_bitcount(i));
    }
}

float benchmark_bitcount()
{
    benchmark_function(bitcount);
}

float benchmark_fast_bitcount()
{
    benchmark_function(fast_bitcount);
}

float benchmark_bitcounts()
{
    float seconds;
    printf("Warming the normal bitcount caches\n");
    benchmark_bitcount();
    printf("Benchmarking normal bitcount\n");
    seconds = benchmark_bitcount();
    printf(
        "Benchmarked normal bitcount, %d " \
        "iterations took %f seconds\n",
        BENCH_MAX, seconds
    );

    printf("Warming the fast bitcount caches\n");
    benchmark_fast_bitcount();
    printf("Benchmarking fast bitcount\n");
    seconds = benchmark_fast_bitcount();
    printf(
        "Benchmarked fast bitcount, %d " \
        "iterations took %f seconds\n",
        BENCH_MAX, seconds
    );
}

int main(void)
{
    test_del_right_most_bit();
    test_bitcounts();
    benchmark_bitcounts();
    return 0;
}
