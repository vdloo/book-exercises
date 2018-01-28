#include <stdio.h>

int main (void)
{
    int c;
    while((c = getchar()) != EOF) {
        switch (c) {
            case '\t':
                printf("\\t");
                break;
            case '\b':
                printf("\\b");
                break;
            case '\\':
                printf("\\\\");
                break;
            default:
                printf("%c", c);
        }
    }
    return 0;
}
