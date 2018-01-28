#include <stdio.h>

#define MAXLINE 1000
#define MINPRINTLEN 80


int my_getline(char line[], int maxinline);

int main(void) 
{
    int len;
    char line[MAXLINE];

	while ((len = my_getline(line, MAXLINE)) > 0) {
		if (len >= MINPRINTLEN) {
            printf("line is longer or equal to %d chars, printing..\n", MINPRINTLEN);
            printf("%s", line);
		}
	}
    return 0;
}


int my_getline(char s[], int lim)
{
	int c, i, read;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		s[i] = c;
	    read = i;
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
