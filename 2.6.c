#include <stdio.h>
#include <assert.h>

/* x 
 * | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | 
 * |128| 64| 32| 16| 8 | 4 | 2 | 1 |
 * | 1 | 0 | 1 | 0 | 1 | 0 | 1 | 0 |
 *  170 = 128 + 32 + 8 + 2 */

/* y
 * | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | 
 * |128| 64| 32| 16| 8 | 4 | 2 | 1 |
 * | 1 | 1 | 1 | 0 | 1 | 1 | 1 | 0 |
 *  238 = 128 + 64 + 32 + 8 + 4 + 2 */

/* setting bits the least significant three bits from y on x at p 4 */

/* x after mutation
 * | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | 
 * |128| 64| 32| 16| 8 | 4 | 2 | 1 |
 * | 1 | 0 | 1 | 1 | 1 | 0 | 1 | 0 |
 * 186 */


/* step 1: create a mask to zero out p, p - 1 and p - 2 in x
 * x & ~((~0 << (p - n + 1)) & (~(~0 << (p + 1))))
 *
 * Why p - n + 1? 
 * - because if n=3 we need p, p - 1, and p - 2
 * - because we bitshift (<<) to p, and the first 
 *   bit is counted as slot 0 not 1
 *
 * Why p + 1?
 * - See (p - n + 1). p is bit (p + 1), it starts at slot 0
 *
 * Create a mask that will zero p - 2 to 0
 * (~0 << (p - n + 1)) 
 * Will create: | 1 | 1 | 1 | 1 | 0 | 0 | 0 |
 *                    p   p-1 p-2
 *
 * Create a mask that will zero p + 1 to 0
 * (~(~0 << (p + 1)))
 * Will create: | 1 | 0 | 0 | 0 | 0 | 0 | 0 |
 *                    p   p-1 p-2
 * And then invert it with the outer (~
 * Will create: | 0 | 1 | 1 | 1 | 1 | 1 | 1 |
 *                    p   p-1 p-2
 *
 * Combine those masks to create a mask that only keeps p to p - 2
 * ~((~0 << (p - n + 1)) & (~(~0 << (p + 1))))
 * Mask 1: | 1 | 1 | 1 | 1 | 0 | 0 | 0 |
 * Mask 2: | 0 | 1 | 1 | 1 | 1 | 1 | 1 |
 * Bitwise AND
 * Mask 3: | 0 | 1 | 1 | 1 | 0 | 0 | 0 |
 *
 * And then finally invert it again so we zero p to p - 2
 * Mask 3: | 1 | 0 | 0 | 0 | 1 | 1 | 1 |
 *               p   p-1 p-2
 *
 * This mask can be bitwise AND with x to zero out p, p - 1 and p - 2
 * Mask 1: | 1 | 0 | 0 | 0 | 1 | 1 | 1 |
 *      x: | 1 | 0 | 1 | 0 | 1 | 0 | 1 |
 *    New: | 1 | 0 | 0 | 0 | 1 | 0 | 1 |
 *
 * step 2: get the lower 3 bits from y and move them up to p, p - 1 and p - 2
 * ((y & ~(~0 << n)) << (p - n + 1))
 *
 * Note:
 * - If n=3, we shift by 3. Not like p where we shift with (p - 1). 
 *   This is because n is the offset from p, not a position in the bit array.
 * - (p - n + 1) because p is the address which starts at 0. 
 *   If we try to move 3 bits we need to move up p - 3 + 1
 *   If we try to move 5 bits we need to move up p - 5 + 1, etc
 *
 * Create a mask that zeroes out all but the first 3 bits
 * (~(~0 << 3))
 * Will create: | 0 | 0 | 0 | 1 | 1 | 1 |
 *
 * Use that mask to get the first 3 bits from y
 * y & (~(~0 << 3))
 *
 * If y is 0177: | 1 | 1 | 1 | 1 | 1 | 1 |
 *  decimal 127
 * Would create: | 0 | 0 | 0 | 1 | 1 | 1 |
 *
 * Then move those bits up to p so they cover p, p - 1 and p - 2
 * (y & (~(~0 << 3)) << (p - 3 + 1))
 * Would create: | 1 | 1 | 1 | 0 | 0 | 0 |
 *
 * step 3: replace p, p - 1 and p - 2 with bits 2, 1 and 0 from y
 * ((x & ~((~0 << (p - n + 1)) & (~(~0 << (p + 1))))) | ((y & ~(~0 << n)) << (p - n + 1)))
 *
 *                 p   p-1 p-2
 *        y: | 0 | 1 | 0 | 1 | 1 | 0 | 1 |
 *        x: | 1 | 0 | 1 | 0 | 1 | 0 | 1 |
 * zeroed x: | 1 | 0 | 0 | 0 | 1 | 0 | 1 |
 * p to p-2: | 0 | 1 | 0 | 1 | 0 | 0 | 0 |
 * Bitwise OR to fill the zeroed p to p - 2 in x with bits 2, 1 and 0 from y
 *   Result: | 1 | 1 | 0 | 1 | 1 | 0 | 1 | */

unsigned int get_least_three_significant_bits(unsigned int bits)
{
	return bits & ~(~0 << 3);
}

unsigned int move_bits_up_n_slots(unsigned int bits, int n)
{
	assert(n > 0);
	return bits << n;
}

unsigned int zero_out_n_to_least_significant(unsigned int bits, int n)
{
	assert(n > 0);
	return bits & (~0 << n);
}

unsigned int zero_out_except_n_to_m(unsigned int bits, int n, int m)
{
	assert(m < n);
	assert(n > 0);
	assert(m >= 0);
	return bits & ((~0 << m) & (~(~0 << (n + 1))));
}

unsigned int zero_out_n_to_m(unsigned int bits, int n, int m)
{
	assert(m < n);
	assert(n > 0);
	assert(m >= 0);
	return bits & ~((~0 << m) & (~(~0 << (n + 1))));
}

void test_zero_out_n_to_m()
{
	unsigned int bits;
	unsigned int ret;

	/* Test zeroing out bits 1 and 0 in 7 */
	bits = 07;
	ret = zero_out_n_to_m(bits, 1, 0);
	printf("Zeroing out bits 1 and 0 in %d gives %d\n", bits, ret);
	assert(ret == 4);

	/* Test zeroing out bits 2, 1 and 0 in 7 */
	bits = 07;
	ret = zero_out_n_to_m(bits, 2, 0);
	printf("Zeroing out bits 2, 1 and 0 in %d gives %d\n", bits, ret);
	assert(ret == 0);

	/* Test zeroing out bits 3 and 2 in 7*/
	bits = 07;
	ret = zero_out_n_to_m(bits, 3, 2);
	printf("Zeroing out bits 3 and 2 in %d gives %d\n", bits, ret);
	assert(ret == 3);

	/* Test zeroing out bits 3 and 2 in 15*/
	bits = 017;
	ret = zero_out_n_to_m(bits, 3, 2);
	printf("Zeroing out bits 3 and 2 in %d gives %d\n", bits, ret);
	assert(ret == 3);

	/* Test zeroing out bits bits 5 to 1 in 7*/
	bits = 0377;
	ret = zero_out_n_to_m(bits, 5, 1);
	/* 
	 * | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | 
	 * |128| 64| 32| 16| 8 | 4 | 2 | 1 |
	 * | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 1 |
	 *   193 = 128 + 64 + 1 */
	printf("Zeroing out bits 5, 4, 3, 2 and 1 in %d gives %d\n", bits, ret);
	assert(ret == 193);
}

void test_zero_out_except_n_to_m()
{
	unsigned int bits;
	unsigned int ret;

	/* Test zeroing out all except bits 1 and 0 in 7 */
	bits = 07;
	ret = zero_out_except_n_to_m(bits, 1, 0);
	printf("Keeping bits 1 and 0 in %d gives %d\n", bits, ret);
	assert(ret == 3);

	/* Test zeroing out all except bits 2, 1 and 0 in 7 */
	bits = 07;
	ret = zero_out_except_n_to_m(bits, 2, 0);
	printf("Keeping bits 2, 1 and 0 in %d gives %d\n", bits, ret);
	assert(ret == 7);

	/* Test zeroing out all except bits 3 and 2 in 7*/
	bits = 07;
	ret = zero_out_except_n_to_m(bits, 3, 2);
	printf("Keeping bits 3 and 2 in %d gives %d\n", bits, ret);
	assert(ret == 4);

	/* Test zeroing out all except bits 3 and 2 in 15*/
	bits = 017;
	ret = zero_out_except_n_to_m(bits, 3, 2);
	printf("Keeping bits 3 and 2 in %d gives %d\n", bits, ret);
	assert(ret == 12);

	/* Test zeroing out all except bits 5 to 1 in 7*/
	bits = 0777777;
	ret = zero_out_except_n_to_m(bits, 5, 1);
	/* 
	 * | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | 
	 * |128| 64| 32| 16| 8 | 4 | 2 | 1 |
	 * | 0 | 0 | 1 | 1 | 1 | 1 | 1 | 0 |
	 *   62 = 32 + 16 + 8 + 4 + 2 */
	printf("Keeping bits 5, 4, 3, 2 and 1 in %d gives %d\n", bits, ret);
	assert(ret == 62);
}

void test_zero_out_n_to_least_significant()
{
	unsigned int bits;
	unsigned int ret;

	/* Test zeroing out bits 2 and 1 in 7*/
	bits = 7;
	ret = zero_out_n_to_least_significant(bits, 2);
	printf("Zeroing out bits 2 and 1 in %d gives %d\n", bits, ret);
	assert(ret == 4);

	/* Test zeroing out bits 3, 2 and 1 in 7*/
	bits = 7;
	ret = zero_out_n_to_least_significant(bits, 3);
	printf("Zeroing out bits 3, 2 and 1 in %d gives %d\n", bits, ret);
	assert(ret == 0);

	/* Test zeroing out bits 3, 2 and 1 in 15*/
	bits = 017;
	ret = zero_out_n_to_least_significant(bits, 3);
	printf("Zeroing out bits 3, 2 and 1 in %d gives %d\n", bits, ret);
	assert(ret == 8);

	/* Test zeroing out bits 4, 3, 2 and 1 in 15*/
	bits = 017;
	ret = zero_out_n_to_least_significant(bits, 4);
	printf("Zeroing out bits 4, 3, 2 and 1 in %d gives %d\n", bits, ret);
	assert(ret == 0);

}

void test_move_bits_up_n_slots()
{
	unsigned int bits;
	unsigned int ret;

	/* Test moving bits up once multiplies the number by 2 */
	bits = 7;
	ret = move_bits_up_n_slots(bits, 1);
	printf("Moving the bits in %d up by 1 gives %d\n", bits, ret);
	assert(ret == 14);

	/* Test moving bits up twice multiplies the number by 4 */
	bits = 7;
	ret = move_bits_up_n_slots(bits, 2);
	printf("Moving the bits in %d up by 1 gives %d\n", bits, ret);
	assert(ret == 28);

	/* Test moving bits up three times multiplies the number by 8 */
	bits = 7;
	ret = move_bits_up_n_slots(bits, 3);
	printf("Moving the bits in %d up by 1 gives %d\n", bits, ret);
	assert(ret == 56);
}

void test_get_at_least_three_significant_bits()
{
	unsigned int bits;
	unsigned int ret;

	/* Test the original value is not mutated */
	bits = 1234;
	get_least_three_significant_bits(bits);
	assert(bits == 1234);

	/* Test up until 7 the least significant bits add up to the int */
	for (bits = 0; bits < 7; bits++) {
		ret = get_least_three_significant_bits(bits);
		printf("The least three significant bits of %d count to %d\n", bits, ret);
		assert(ret == bits);
	}

	/* Test at 8 the least significant bits are all off */
	bits = 8;
	ret = get_least_three_significant_bits(bits);
	printf("The least three significant bits of %d count to %d\n", bits, ret);
	assert(ret == 0);

	/* Test that anything larger than 8 is cut off from the result, 
	 * those are the bits higher than the first three slots */
	for (bits = 9; bits < 16; bits++) {
		ret = get_least_three_significant_bits(bits);
		printf("The least three significant bits of %d count to %d\n", bits, ret);
		assert(ret == bits - 8);
	}
}

unsigned setbits(unsigned int x, int p, int n, unsigned int y) {
    return ((x & (~((~0 << (p - n + 1)) & (~(~0 << (p + 1)))))) | ((y & ~(~0 << n)) << (p - n + 1)));
}

void test_setbits()
{
	unsigned int x, y, ret;
	int p, n;

    x = 170;
	y = 238;
    p = 4;
    n = 3;

	ret = setbits(x, p, n, y);
    printf(
        "The result of copying the last %d bits of "\
		"%d to position %d of %d is %d\n",
        n, y, p, x, ret
    );
    assert(ret == 186);

    x = 213;
	y = 121;
    p = 4;
    n = 4;

	ret = setbits(x, p, n, y);
    printf(
        "The result of copying the last %d bits of "\
		"%d to position %d of %d is %d\n",
        n, y, p, x, ret
    );
    assert(ret == 211);

    x = 5732;
	y = 9823;
    p = 6;
    n = 3;

	ret = setbits(x, p, n, y);
    printf(
        "The result of copying the last %d bits of "\
		"%d to position %d of %d is %d\n",
        n, y, p, x, ret
    );
    assert(ret == 5748);
}

int main(void)
{
	test_get_at_least_three_significant_bits();
	test_move_bits_up_n_slots();
	test_zero_out_n_to_least_significant();
	test_zero_out_except_n_to_m();
	test_zero_out_n_to_m();
	test_setbits();
    return 0;
}

