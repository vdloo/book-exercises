#include <stdio.h>

#define MAXLINE 1000

int my_getline(char line[], int maxline);
void my_copy(char to[], char from[]);

int main(void)
{
	int len, max, c;
	char line[MAXLINE];
	char longest[MAXLINE];

	max = 0;
	while ((len = my_getline(line, MAXLINE)) > 0) {
		if (line[len - 1] != '\n') {
			while ((c = getchar()) != EOF && c != '\n') {
				len++;
			}
		}
		if (len > max) {
			max = len;
			my_copy(longest, line);
		}
	}
	if (max > 0) {
		printf("longest line is %d long\n", max);
		printf("%s", longest);
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
	if (read == (lim - 2)) {
		while ((c = getchar()) != EOF && c != '\n') {
			++i;
		}
	}
	return i;
}

void my_copy(char to[], char from[])
{
	int i;

	i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}
