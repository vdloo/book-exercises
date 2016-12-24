#include <stdio.h>

int main (void)
{
	char prev_c;
	char cur_c = ' ';
	int loop = 1;
	while (loop) {
		loop = (cur_c = getchar()) != EOF;
		if (cur_c != ' ') {
			printf("%c", prev_c);
		}
		prev_c = cur_c;
	}
    return 0;
}
