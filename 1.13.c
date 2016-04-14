#include <stdio.h>
#include <time.h>

void paint_histogram(int *word_lengths)
{
	int i, j, largest = 20;
	int bar_mapping[12];
	for (i = largest; i >= 0; --i) {
		for (j = 0; j < 80; j++) {
			if (word_lengths[j] >= i) {
				printf("__");
			} else {
				printf("  ");
			}
		}
		printf("\n");
	}
}

/* count digits, white space, others */
main()
{
	int c, i, chars_in_word = 0;
	int word_lengths[80];
	struct timespec time;
	time.tv_sec = 0;
	time.tv_nsec = 80*1000000L;

	for (i = 0; i < 80; ++i) {
		word_lengths[i] = 0;
	}

	i = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') {
			if (i < 80) {
				word_lengths[i] = chars_in_word;
				++i;
			} else {
				system("clear");
				paint_histogram(word_lengths);
				nanosleep(&time, NULL);
				i = 0;
			}
			chars_in_word = 0;
		} else {
			++chars_in_word;
		}
	}
}
