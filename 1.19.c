#include <stdio.h>

#define MAXLINE 1000

int my_getline(char line[], int maxinline);
void reverse(char line[], int len);

int main(void) 
{
    int len;
    char line[MAXLINE];

	while ((len = my_getline(line, MAXLINE)) > 0) {
		if (len > 0) {
            reverse(line, len);
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

void reverse(char s[], int lim)
{
    char c;
    int i, j = 0;
    for (i = (lim - 1); (i >= 0 && j < i); --i) {
        switch(s[i]) {
            case '\0': case '\n':
                break;
            default:
                c = s[j];
                s[j] = s[i];
                s[i] = c;
                j++;
        }
    }
}

