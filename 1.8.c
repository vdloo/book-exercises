#include <stdio.h>

/* count blanks, tabs and newlines in input */
main()
{
	int c, blanks, tabs, newlines;
	blanks = tabs = newlines = 0;
	while ((c = getchar()) != EOF) {
		switch(c) {
			case ' ':
				++blanks;
				break;
			case '\t':
				++tabs;
				break;
			case '\n':
				++newlines;
				break;
		}
	}
	printf("blanks:%d, tabs:%d, newlines:%d\n", blanks, tabs, newlines);
}
