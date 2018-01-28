#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAXLEN 1000

void squeeze(char haystack[], char needles[])
{
    int i, j, c = 0;
    int can_skip;
    int stop = 0;
    for (i = 0; stop != 1; i++) {
        can_skip = 0;
        for (j = 0; needles[j] != '\0'; j++) {
            if (needles[j] == haystack[i]) {
                can_skip = 1;
            }
        }
        if (!can_skip) {
            haystack[c] = haystack[i];
            if (haystack[c] == '\0') {
                stop = 1;
            }
            c++;
        }
    }
}

void test_squeeze()
{
    char haystack[MAXLEN];
    char needles[MAXLEN];

    strcpy(haystack, "test 123 this is a test");
    strcpy(needles, " 2 ae");
    squeeze(haystack, needles);
    assert(strcmp(haystack, "tst13thisistst") == 0);
    printf("'test 123 this is a test' without ' 2 ae' is 'tst13thisistst'\n");

    strcpy(haystack, "12345678");
    strcpy(needles, "abcdefg");
    squeeze(haystack, needles);
    assert(strcmp(haystack, "12345678") == 0);
    printf("'12345678' without 'abcdefg' is '12345678'\n");

    strcpy(haystack, "abcdefgabcdefg");
    strcpy(needles, "abcabcg");
    squeeze(haystack, needles);
    assert(strcmp(haystack, "defdef") == 0);
    printf("'abcdefgabcdefg' without 'abcabcg' is 'defdef'\n");
}

int main(void)
{
    test_squeeze();
    return 0;
}

