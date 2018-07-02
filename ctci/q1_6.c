#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Write a function that 'compresses' a string by turning
   'baaab' into ba3b', etc. If the 'compression' does not
   shorten the string, keep the original characters. For
   example, 'baab' would not become 'ba2b' but remain
   'baab' because that is just as long. But 'bbaab'
   should become 'b2a2b' and not 'bba2b' etc. */

/*
  $ gcc q1_6.c ; ./a.out ; echo $?
  'baaab' becomes 'ba3b': ba3b
  'baab' stays 'baab': baab
  'bab' stays 'bab': bab
  'bb' stays 'bb': bb
  'bbb' becomes 'b3': b3
  'some longer string' stays 'some longer string': some longer string
  'bbbaaabbbaaa' becomes 'b3a3b3a3': b3a3b3a3
  'bbbabaaa' becomes 'b3aba3': b3aba3
  'bbaab' becomes 'bbaab': bbaab
  0
*/


char * simple_compress(char str[])
{
    size_t buf_len = strlen(str);
    char *new_str = calloc(buf_len, sizeof(char));
    if (new_str == '\0') {
        fprintf(stderr, "Failed to allocate memory for new_str buffer\n");
        exit(1);
    }
    
    int i = 0, j = 0, c = 1;
    char cur_char, prev_char = -1;
    for (i = 0; i <= buf_len; i++) {
        cur_char = str[i];
        if (cur_char == prev_char) {
            c++;
            if (c > 9) {
                fprintf(stderr, "This program can only handle 9 consecutive chars\n");
                exit(1);
            }
        } else if (prev_char != -1) {
            new_str[j] = prev_char;
            j++;
            if (c == 2) {
                new_str[j] = prev_char;
                j++;
            } else if (c > 2) {
                new_str[j] = c + '0';
                j++;
            }
            c = 1;
        }
        prev_char = cur_char;
    }

    return strlen(str) > strlen(new_str) ? new_str : str;
}

void test_simple_compress()
{
    char * string;
    char * compressed;

    asprintf(&string, "baaab");
    compressed = simple_compress(string);
    printf("'baaab' becomes 'ba3b': %s\n", compressed);
    assert(strcmp(compressed, "ba3b") == 0);
    free(compressed);

    asprintf(&string, "baab");
    compressed = simple_compress(string);
    printf("'baab' stays 'baab': %s\n", compressed);
    assert(strcmp(compressed, "baab") == 0);
    free(compressed);

    asprintf(&string, "bab");
    compressed = simple_compress(string);
    printf("'bab' stays 'bab': %s\n", compressed);
    assert(strcmp(compressed, "bab") == 0);
    free(compressed);

    asprintf(&string, "bb");
    compressed = simple_compress(string);
    printf("'bb' stays 'bb': %s\n", compressed);
    assert(strcmp(compressed, "bb") == 0);
    free(compressed);

    asprintf(&string, "bbb");
    compressed = simple_compress(string);
    printf("'bbb' becomes 'b3': %s\n", compressed);
    assert(strcmp(compressed, "b3") == 0);
    free(compressed);

    asprintf(&string, "some longer string");
    compressed = simple_compress(string);
    printf("'some longer string' stays 'some longer string': %s\n", compressed);
    assert(strcmp(compressed, "some longer string") == 0);
    free(compressed);

    asprintf(&string, "bbbaaabbbaaa");
    compressed = simple_compress(string);
    printf("'bbbaaabbbaaa' becomes 'b3a3b3a3': %s\n", compressed);
    assert(strcmp(compressed, "b3a3b3a3") == 0);
    free(compressed);

    asprintf(&string, "bbbabaaa");
    compressed = simple_compress(string);
    printf("'bbbabaaa' becomes 'b3aba3': %s\n", compressed);
    assert(strcmp(compressed, "b3aba3") == 0);
    free(compressed);

    asprintf(&string, "bbaab");
    compressed = simple_compress(string);
    printf("'bbaab' becomes 'bbaab': %s\n", compressed);
    assert(strcmp(compressed, "bbaab") == 0);
    free(compressed);
}

int main(void)
{
    test_simple_compress();
    return 0;
}
