#include <stdio.h>

#define TABSTOP 4
#define MAXLINE 1000

int my_getline(char line[], int maxinline);
void print_detabbed(char line[], int limit);

int main(void)
{
    int len;
    char line[MAXLINE];

	while ((len = my_getline(line, MAXLINE)) > 0) {
		if (len > 0) {
            print_detabbed(line, len);
		}
	}
    return 0;
}

void print_detabbed(char s[], int lim)
{
    int i, j, w, c = 0;
    for (i = 0; i < lim; ++i) {
        if (s[i] == '\t') {
            w = TABSTOP - (c % TABSTOP);
            for (j = 0; j < w; j++) {
                printf(" ");
                c++;
            }
        } else {
            printf("%c", s[i]);
            c++;
        }
    }
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
