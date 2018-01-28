#include <stdio.h>

#define MAXLINE 1000

void my_getline(char line[], int maxinline);

int main(void)
{
    int len;
    char line[MAXLINE];
	printf("input:\t");
	my_getline(line, MAXLINE);
	printf("output:\t%s", line);
	return 0;
}

void my_getline(char s[], int lim)
{
	int c, i, read;

	for (i = 0; i < lim - 1; ++i) {
		c = getchar();
	    if (c == EOF) {
			break;
		} 
		if (c == '\n') {
			break;
		}
		s[i] = c;
	    read = i;
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
}
