#include <stdio.h>

#define MAXLINE 1000

int my_getline(char line[], int maxinline);

int main(void) 
{
    int len, i;
    int not_done_marker;
    char line[MAXLINE];

	while ((len = my_getline(line, MAXLINE)) > 0) {
        not_done_marker = 1;
        for (i = (len - 1); not_done_marker && (i >= 0); --i) {
            switch(line[i]) {
                case '\0': case '\n':
                    break;
                case '\t': case ' ':
                    line[i] = '\n';
                    if ((i + 1) <= (len - 1)) {
                        line[i + 1] = '\0';
                    }
                    break;
                default:
                    /* encountered non-blank and non-tab */
                    not_done_marker = 0;
            }
        }
		if (i > 0) {
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
