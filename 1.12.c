#include <stdio.h>


int check_if_whitespace(char c) {
	switch (c) {
		case '\t': 
		case '\n':
		case ' ':
			return 1;
		default:
			return 0;
	}
}

int main(void)
{
	int cur_c, cur_is_whitespace, prev_was_whitespace = 1;
	while ((cur_c = getchar()) != EOF) {
		cur_is_whitespace = check_if_whitespace(cur_c);
		if (cur_is_whitespace == 1) {
			if (prev_was_whitespace == 0) {
				printf("\n");
			}
		}
		else {
			printf("%c", cur_c);
		}
		prev_was_whitespace = cur_is_whitespace;
	}
    return 0;
}
