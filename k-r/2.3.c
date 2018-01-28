#include <stdio.h>
#include <assert.h>

#define HEX_DISEASE 219540062
#define HEX_DEADBEEF 3735928559
#define HEX_DEADCODE 3735929054

unsigned long htoi(char hex[]);

void test_htoi()
{
    printf("0xD15EA5E translates to %lu\n", htoi("0xD15EA5E"));
    assert(htoi("0xD15EA5E") == HEX_DISEASE);
    printf("0XD15EA5E translates to %lu\n", htoi("0XD15EA5E"));
    assert(htoi("0XD15EA5E") == HEX_DISEASE);
    printf("0xd15ea5e translates to %lu\n", htoi("0xd15ea5e"));
    assert(htoi("0xd15ea5e") == HEX_DISEASE);

    printf("0xDEADBEEF translates to %lu\n", htoi("0xDEADBEEF"));
    assert(htoi("0xDEADBEEF") == HEX_DEADBEEF);
    printf("0XDEADBEEF translates to %lu\n", htoi("0XDEADBEEF"));
    assert(htoi("0XDEADBEEF") == HEX_DEADBEEF);
    printf("0xdeadbeef translates to %lu\n", htoi("0xdeadbeef"));
    assert(htoi("0xdeadbeef") == HEX_DEADBEEF);

    printf("0xDEADC0DE translates to %lu\n", htoi("0xDEADC0DE"));
    assert(htoi("0xDEADC0DE") == HEX_DEADCODE);
    printf("0XDEADC0DE translates to %lu\n", htoi("0XDEADC0DE"));
    assert(htoi("0XDEADC0DE") == HEX_DEADCODE);
    printf("0xdeadc0de translates to %lu\n", htoi("0xdeadc0de"));
    assert(htoi("0xdeadc0de") == HEX_DEADCODE);
}

int main(void)
{
    test_htoi();
    return 0;
}

int is_uppercase(char c)
{
    return (c >= 'A' && c <= 'Z');
}

char lower(char c)
{
    if (is_uppercase(c)) {
        return c + 'a' - 'A';
    } else {
        return c;
    }
}

unsigned long my_pow(unsigned long base, int exponent)
{
    int i;
    unsigned long out = base;
    if (exponent > 0) {
        for (i = 1; i < exponent; i++) {
            out *= base;
        }
    } else {
        out = 1;
    }
    return out;
}

unsigned long htoi(char hex[])
{
    char c;
    unsigned long out = 0;
    int i = 0;
    int j = 0;
    /* Count the characters in the char array */
    while (c = hex[j] != '\0') {
        j++;
    }
    /* Reverse loop over the character array */
    for (j-- ; j >= 0; j--, i++) {
        c = lower(hex[j]);

        /* Ignore leading 0x and 0X */
        if (j == 1 && c == 'x' && hex[0] == '0') {
            break;
        }

        /* Translate the hex value represented by the ascii char 
         * to the decimal equivalent  */
        if (c > '9') {
            c -= 'a';
            c += 10;
        } else {
            c -= '0';
        }

        /* Multiply every char with 16 to the power of the reverse 
         * char position */
        out += c * my_pow(16, i);
    }
    return out;
}
