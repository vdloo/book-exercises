#include <stdio.h>
#include <assert.h>

char lower(char c)
{
	return (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c;
}

void test_lower()
{
    printf("A becomes %c\n", lower('A'));
    assert(lower('A') == 'a');

    printf("B becomes %c\n", lower('A'));
    assert(lower('B') == 'b');

    printf("a stays %c\n", lower('A'));
    assert(lower('a') == 'a');

    printf("b stays %c\n", lower('A'));
    assert(lower('b') == 'b');
}

int main(void)
{
    test_lower();
    return 0;
}

