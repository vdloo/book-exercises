#include <stdio.h>
#include <assert.h>

/* Test 1
 * | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | 
 * |128| 64| 32| 16| 8 | 4 | 2 | 1 |
 * | 1 | 0 | 1 | 1 | 1 | 0 | 1 | 0 |
 *  186 = 128 + 32 + 16 + 8 + 2
 *
 *  Rotate to the right by 2 bits
 * | 1 | 0 | 1 | 0 | 1 | 1 | 1 | 0 |
 * 174 = 128 + 32 + 8 + 4 + 2 */

/* Test 2
 * | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | 
 * |128| 64| 32| 16| 8 | 4 | 2 | 1 |
 * | 0 | 1 | 1 | 1 | 1 | 0 | 1 | 0 |
 *  122 = 64 + 32 + 16 + 8 + 2
 *
 * Note: the MSB is 6, bit 7 is 0 so we 
 * shift to slot 6 not 7 like in test 1.
 *  Rotate to the right by 5 bits
 * | 0 | 1 | 1 | 0 | 1 | 0 | 1 | 1 |
 * 107 = 64 + 32 + 8 + 2 + 1 */

int most_significant_bit_position(unsigned int x)
{
    unsigned out = 0;
    while (x >>= 1) {
	    out++;
    }
    return out;
}

unsigned rightrot(unsigned int x, int n)
{
    int bits = most_significant_bit_position(x);
    return (x >> n) | ((x & ~(~0 << n)) << (bits - n + 1));
}

void test_rightrot()
{
    unsigned int x, ret;
    int n;

    x = 186;
    n = 2;
    ret = rightrot(x, n);
    printf(
        "The result of right rotating %d bits "\
        "of %d is %d\n",
        n, x, ret
    );
    assert(ret == 174);

    x = 122;
    n = 5;
    ret = rightrot(x, n);
    printf(
        "The result of right rotating %d bits "\
        "of %d is %d\n",
        n, x, ret
    );
    assert(ret == 107);
}

int main(void)
{
    test_rightrot();
    return 0;
}

