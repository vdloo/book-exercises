#include <stdio.h>
#include <assert.h>

/* Test 1
 * | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | 
 * |128| 64| 32| 16| 8 | 4 | 2 | 1 |
 * | 1 | 0 | 1 | 0 | 1 | 0 | 1 | 0 |
 *  170 = 128 + 32 + 8 + 2 
 *
 * Invert p = 5, n = 3
 * | 1 | 0 | 0 | 1 | 0 | 0 | 1 | 0 |
 * 146 = 170 - 32 + 16 - 8 */

/* Test 2
 * | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | 
 * |128| 64| 32| 16| 8 | 4 | 2 | 1 |
 * | 1 | 0 | 1 | 1 | 1 | 0 | 1 | 0 |
 *  186
 *
 * Invert p = 6, n = 4
 * | 1 | 1 | 0 | 0 | 0 | 0 | 1 | 0 |
 *  194 = 186 + 64 - 32 - 16 - 8 */


unsigned invert(unsigned int x, int p, int n) {
    /* This could also be done way shorter with a XOR and a mask where only p to p - n is 1. */
    return (x & (~((~0 << (p - n + 1)) & (~(~0 << (p + 1)))))) | (~x & ((~0 << (p - n + 1)) & (~(~0 << (p + 1)))));
}

void test_invert()
{
    unsigned int x, ret;
    int p, n;

    x = 170;
    p = 5;
    n = 3;

    ret = invert(x, p, n);
    printf(
        "The result of inverting the %d bits "\
        "from position %d downward of %d is %d\n",
        n, p, x, ret
    );
    assert(ret == 146);

    x = 186;
    p = 6;
    n = 4;

    ret = invert(x, p, n);
    printf(
        "The result of inverting the %d bits "\
        "from position %d downward of %d is %d\n",
        n, p, x, ret
    );
    assert(ret == 194);
}

int main(void)
{
    test_invert();
    return 0;
}

