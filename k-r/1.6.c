#include <stdio.h>

int main(void)
{
    int i = getchar() != EOF;
    if (i == 1) {
	/* it does not equal EOF if you send input over stdin*/
        printf("getchar() does not equal EOF\n");
    }
    else {
	/* it does equal EOF if you ctrl + d */
        printf("getchar() equals EOF\n");
    }
    return 0;
}
