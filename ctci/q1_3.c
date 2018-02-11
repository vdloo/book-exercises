#include <stdio.h>
#include <string.h>
#include <assert.h>

/* Write a function that takes a string and its length
   and returns the string with the spaces replaced with
   '%20'. Assume that the string that is passed in has
   enough space for additional characters. */

const char * replace_all_spaces(char str[], int length)
{
    char tmp;
    int i, j, new_length;
    int space_count = 0;

    for (i = 0; i < length; i++) {
        if (str[i] == ' ') {
            space_count++;
        }
    }

    /* All spaces wil add two additional characters in length */
    new_length = length + space_count * 2;

    str[new_length] = '\0';
    j = 1;
    for (i = new_length - 1; i >= 0; i--) {
      tmp = str[length - j];
      if (tmp == ' ') {
          str[i] = '0';
          str[i - 1] = '2';
          str[i - 2] = '%';
          i -= 2;
      } else {
          str[i] = str[length - j];
      }
      j++;
    }

    return str;
}

void test_replace_all_spaces()
{
    char string[24];
    sprintf(string, "abc ");
    printf("'abc ' becomes '%s'\n", replace_all_spaces(string, strlen(string)));
    assert(strcmp(replace_all_spaces(string, strlen(string)), "abc%20") == 0);

    sprintf(string, " abc");
    printf("' abc' becomes '%s'\n", replace_all_spaces(string, strlen(string)));
    assert(strcmp(replace_all_spaces(string, strlen(string)), "%20abc") == 0);

    sprintf(string, " a b c ");
    printf("' a b c ' becomes '%s'\n", replace_all_spaces(string, strlen(string)));
    assert(strcmp(replace_all_spaces(string, strlen(string)), "%20a%20b%20c%20") == 0);

    sprintf(string, "abc");
    printf("'abc' stays '%s'\n", replace_all_spaces(string, strlen(string)));
    assert(strcmp(replace_all_spaces(string, strlen(string)), "abc") == 0);

    sprintf(string, "a-b-c");
    printf("'a-b-c' stays %s\n", replace_all_spaces(string, strlen(string)));
    assert(strcmp(replace_all_spaces(string, strlen(string)), "a-b-c") == 0);
}

int main(void)
{
    test_replace_all_spaces();
    return 0;
}
