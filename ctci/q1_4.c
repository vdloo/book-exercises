#include <stdio.h>
#include <assert.h>

/* Write a function that checks if a string is a
   permutation of a palindrome or not */

struct {
    /* 26 bit bitfield to hold the alphabet */
    unsigned int bitfield : 26;
} BitField;

/* return 0 if permutation of palindrome, 1 if not */
int permutation_is_palindrome(char str[])
{
    int i, bit_pos;
    BitField.bitfield = 0;

    /* for each character, get the alphabetical index
       where a is 0 and z is 25 */
    for (i = 0; str[i] != '\0'; i++) {
        bit_pos = str[i] - 'a';

        /* Toggle the bit corresponding to the index */
        BitField.bitfield ^= 1U << bit_pos;
    }

  /* The input is a permutation of a palindrome if
     there is maximally one bit set to 1 in the bit
     field. If there are 0 bits set to 0 it is a
     string with even characters, if 1 bit is set
     to 1 the string is odd with a middle character
     that is allowed to be uneven. If there are more
     no permutation is a palindrome */
   return BitField.bitfield != 0 && (
       /* checking if exactly 1 bit is set to 1 by
          inverting the bitfield and AND-ing that
          with the original. If that equals 0 there
          is 1 bit set to 1 but no more or less. */
       BitField.bitfield & (BitField.bitfield - 1)
   ) != 0;
}

void test_permutation_is_palindrome()
{
    printf(
        "'abc' is a palindrome permutation: '%i'\n",
        permutation_is_palindrome("abc")
    );
    assert(permutation_is_palindrome("abc") == 1);

    printf(
        "'baba' is a palindrome permutation: '%i'\n",
        permutation_is_palindrome("baba")
    );
    assert(permutation_is_palindrome("baba") == 0);

    printf(
        "'aba' is a palindrome permutation: '%i'\n",
        permutation_is_palindrome("aba")
    );
    assert(permutation_is_palindrome("aba") == 0);

    printf(
        "'abba' is a palindrome permutation: '%i'\n",
        permutation_is_palindrome("abba")
    );
    assert(permutation_is_palindrome("abba") == 0);

    printf(
        "'somelongersentence' is a palindrome permutation: '%i'\n",
        permutation_is_palindrome("somelongersentence")
    );
    assert(permutation_is_palindrome("some longer sentence") == 1);

    printf(
        "'legovogel' is a palindrome permutation: '%i'\n",
        permutation_is_palindrome("legovogel")
    );
    assert(permutation_is_palindrome("legovogel") == 0);

    printf(
        "'eggolvole' is a palindrome permutation: '%i'\n",
        permutation_is_palindrome("eggolvole")
    );
    assert(permutation_is_palindrome("eggolvole") == 0);
}

int main(void)
{
    test_permutation_is_palindrome();
    return 0;
}
