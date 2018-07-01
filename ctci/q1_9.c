#include <stdio.h>
#include <string.h>
#include <assert.h>

/* Given two strings, write code to check if s2 is a rotation of s1 using
 * only a single call to an is_substring function */


int is_rotation(char s1[], char s2[]) {
    /* Returns 1 if s2 is a rotation of s1, so for example
     * if s1 is waterbottle and s2 is erbottlewat it will
     * return 1, if is it not a rotation it will return 0 */
    size_t buf_len = strlen(s1);
    /* minus one because we will overwrite the null byte of the first copy */
    char buffer[(buf_len * 2) - 1];
    strcpy(buffer, s1);
    strcpy(buffer + buf_len, s1);
    return strstr(buffer, s2) != '\0';
}

void test_is_rotation() {
    printf(
            "Verifying that is_rotation detects waterbottle "
            "as a rotation of waterbottle\n"
    );
    assert(is_rotation("waterbottle", "waterbottle"));

    printf(
        "Verifying that is_rotation detects erbottlewat "
        "as a rotation of waterbottle\n"
    );
    assert(is_rotation("waterbottle", "erbottlewat"));

    printf(
            "Verifying that is_rotation detects frbottlewat "
            "as not a rotation of waterbottle\n"
    );
    assert(is_rotation("waterbottle", "frbottlewat") == 0);

    printf(
            "Verifying that is_rotation detects test123 "
            "as not a rotation of waterbottle\n"
    );
    assert(is_rotation("waterbottle", "test123") == 0);

    printf(
            "Verifying that is_rotation detects waterbottle "
            "as not a rotation of test123\n"
    );
    assert(is_rotation("test123", "waterbottle") == 0);
}

int main(void) {
    test_is_rotation();
    return 0;
}
