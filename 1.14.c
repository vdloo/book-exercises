#include <stdio.h>

void print_header(int *ndigit, int nwhite, int nother)
{
	int i;
	printf("digits = ");
	for (i = 0; i < 10; ++i) {
		printf(" %d", ndigit[i]);
	}
	printf(", white space = %d, other = %d\n", nwhite, nother);
}

int get_largest(int *ndigit, int nwhite, int nother) 
{
	int i, largest = 0;
	for (i = 0; i < 10; ++i) {
		if (ndigit[i] > largest) {
			largest = ndigit[i];
		}
	}
	if (nwhite > largest) {
		largest = nwhite;
	}
	if (nother > largest) {
		largest = nother;
	}
	return largest;
}

void paint_histogram(int *ndigit, int nwhite, int nother)
{
	int i, j, largest = get_largest(ndigit, nwhite, nother);
	int bar_mapping[12];
	for (i = largest; i >= 0; --i) {
		for (j = 0; j < 12; j++) {
			if (j < 10) {
				if (ndigit[j] >= i) {
					printf("____");
				} else {
					printf("    ");
				}
			} else if (j == 11) {
				if (nwhite >= i) {
					printf("____");
				} else {
					printf("    ");
				}
			} else if (j == 12) {
				if (nother >= i) {
					printf("____");
				} else {
					printf("    ");
				}
			}
		}
		printf("\n");
	}
}

/* count digits, white space, others */
int main(void)
{
	int c, i, nwhite, nother;
	int ndigit[10];

	nwhite = nother = 0;
	for (i = 0; i < 10; ++i) {
		ndigit[i] = 0;
	}

	while ((c = getchar()) != EOF) {
		if (c >= '0' && c <= '9') {
			++ndigit[c-'0'];
		} else if (c == ' ' || c == '\n' || c == '\t') {
			++nwhite;
		} else {
			++nother;
		}
	}

	print_header(ndigit, nwhite, nother);
	paint_histogram(ndigit, nwhite, nother);
    return 0;
}
