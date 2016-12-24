#include <stdio.h>

#define TABSTOP 4
#define MAXLINE 1000

int my_getline(char line[], int maxinline);
void print_entabbed(char line[], int limit);

int main(void)
{
    int len;
    char line[MAXLINE];

	while ((len = my_getline(line, MAXLINE)) > 0) {
		if (len > 0) {
            print_entabbed(line, len);
		}
	}
    return 0;
}

void print_entabbed(char s[], int lim)
{
    int i, j, to_next_tabstop, w = 0, c = 0;
    for (i = 0; i < lim; ++i) {
        if (s[i] == '\t') {
            w += TABSTOP;
        } else if (s[i] == ' ') {
            w++;
        } else {
            while (w > 0) {
                to_next_tabstop = TABSTOP - (c % TABSTOP);
                if (w >= to_next_tabstop) {
                    printf("\t");
                    w -= to_next_tabstop;
                    c += to_next_tabstop;
                } else {
                    for (j = 0; j < w; j++) {
                        printf(" ");
                    }
                    c += w;
                    w = 0;
                }
            }
            printf("%c", s[i]);
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
