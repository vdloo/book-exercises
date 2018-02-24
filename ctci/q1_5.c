#include <stdio.h>
#include <assert.h>

/* Write a function that checks if a string is zero or one
   character insertion, removal or replacement away. */

/* return 0 if max 1 edit away, 1 if not */
int max_one_edit_away(char str1[], char str2[])
{
    int i, j, misses = 0;
    for (i = 0, j = 0; str1[i] != '\0' && str2[j] != '\0'; i++, j++) {
        if (str1[i] != str2[j]) {
            misses++;
            if (str1[i + 1] == str2[j]) {
                i++;
            } else if (str1[i] == str2[j + 1]) {
                j++;
            }
            if (misses > 1) {
                return 1;
            }
        }
    }
    if (str1[i] == '\0' && str2[j] == '\0') {
        return 0;
    } else {
        misses++;
        return misses > 1;
    }
}

void test_max_one_edit_away()
{
    printf(
        "'pale' -> 'ple' is max 1 edit away: '%i'\n",
        max_one_edit_away("pale", "ple")
    );
    assert(max_one_edit_away("pale", "ple") == 0);

    printf(
        "'pales' -> 'pale' is max 1 edit away: '%i'\n",
        max_one_edit_away("pales", "pale")
    );
    assert(max_one_edit_away("pales", "pale") == 0);

    printf(
        "'pale' -> 'bale' is max 1 edit away: '%i'\n",
        max_one_edit_away("pale", "bale")
    );
    assert(max_one_edit_away("pale", "bale") == 0);

    printf(
        "'pale' -> 'bake' is max 1 edit away: '%i'\n",
        max_one_edit_away("pale", "bake")
    );
    assert(max_one_edit_away("pale", "bake") == 1);

    printf(
        "'plll' -> 'plle' is max 1 edit away: '%i'\n",
        max_one_edit_away("plll", "plle")
    );
    assert(max_one_edit_away("plll", "plle") == 0);

    printf(
        "'plllll' -> 'plllp' is max 1 edit away: '%i'\n",
        max_one_edit_away("plllll", "plllp")
    );
    assert(max_one_edit_away("plllll", "plllp") == 1);

    printf(
        "'plllp' -> 'plllll' is max 1 edit away: '%i'\n",
        max_one_edit_away("plllp", "plllll")
    );
    assert(max_one_edit_away("plllp", "plllll") == 1);
}

int main(void)
{
    test_max_one_edit_away();
    return 0;
}
