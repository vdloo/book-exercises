#include <stdio.h>

#define TABSTOP 4
#define COLWIDTH 20
#define MAXLINE 1000

int my_getline(char line[], int maxinline);
void print_wrapped(char line[], int limit);

int main(void)
{
    int len;
    char line[MAXLINE];

	while ((len = my_getline(line, MAXLINE)) > 0) {
		if (len > 0) {
            print_wrapped(line, len);
		}
	}
    return 0;
}

void print_wrapped(char s[], int lim)
{
    int i, j, until_next, c=0;
    for (i = 0; i < lim; ++i) {
        /* count how many chars until next not whitespace or tab char */
        until_next = 0;
        for (j = i; j < lim; ++j) {
            if (s[j] != ' ' && s[j] != '\t') {
                /* if char is not whitespace or tab, exit loop */
                break;
            } else if (s[j] == ' ') {
                /* if char is whitespace, increment until_next with one */
                until_next++;
            } else if (s[j] == '\t') {
                /* if char is tab, increment until_next with the amount of 
                 * spaces that the tab would create for the defined tabstop */
                until_next += TABSTOP - ((c + until_next + 1) % TABSTOP);
            }
        }
        if (until_next > 0 && (c + 1 + until_next) >= COLWIDTH) {
            printf("\n");
            /* reset the column counter because we printed a newline and 
             * are now on a new line */
            c = 0;  
            /* fast forward to the first next not whitespace or tab char */
            i = j;
        } else if (s[i] != '\n' && c + 1 >= COLWIDTH) {
            /* in case of one word without spaces or tabs that is longer 
             * than the allowed colwidth, break up that word with a dash 
             * and print a newline. After that reset the column counter */
            printf("-\n");
            c = 0;
        }
        /* print the character and increment the column counter */
        printf("%c", s[i]);
        c++;
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
