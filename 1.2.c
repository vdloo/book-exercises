#include <stdio.h>

int main(void)
{
    printf("Printing alert (bell) character \a.\n");
    printf("Printing backspace character \b.\n");
    printf("Printing formfeed character \f.\n");
    printf("Printing carriage return character \r.\n");
    printf("Printing vertical tab character \v.\n");
    printf("Printing backslash character \\.\n");
    printf("Printing question mark character \?.\n");
    printf("Printing single quote character \'.\n");
    printf("Printing double quote character \".\n");
    printf("Printing octal number %o.\n", '\012');
    printf("Printing hex number %X.\n", '\x12');
    printf("Done!\n");
    return 0;
}
