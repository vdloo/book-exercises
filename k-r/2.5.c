#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAXLEN 1000

int any(char haystack[], char needles[])
{
    int i, j;
    for (i = 0; haystack[i] != '\0'; i++) {
        for (j = 0; needles[j] != '\0'; j++) {
            if (needles[j] == haystack[i]) {
                return i;
            }
        }
    }
    return -1;
}

void test_any()
{
    char haystack[MAXLEN];
    char needles[MAXLEN];
    int ret;

    strcpy(haystack, "test 123 this is a test");
    strcpy(needles, "8 4z5qlm2");
    ret = any(haystack, needles);
    printf(
        "The first char from '8 4z5qlm2' is in 'test 123 this is a test' at character %d\n",
        ret
    );
    assert(ret == 4);

    strcpy(haystack, "12345678");
    strcpy(needles, "abcdefg");
    ret = any(haystack, needles);
    printf(
        "The first char from 'abcdefg' is in '12345678' at character %d (not in string)\n",
        ret
    );
    assert(ret == -1);


    strcpy(haystack, "test 123 this is a test");
    strcpy(needles, "321");
    ret = any(haystack, needles);
    printf(
        "The first char from '321' is in 'test 123 this is a test' at character %d\n",
        ret
    );
    assert(ret == 5);
}

int main(void)
{
    test_any();
    return 0;
}

