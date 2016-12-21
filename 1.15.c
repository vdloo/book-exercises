#include <stdio.h>

float celcius(int fahr) {
	float celsius;
	celsius = 5 * (fahr - 32) / 9;
	return celsius;
}

main()
{
	float fahr;
	int lower, upper, step;

	lower = 0;
	upper = 300;
	step = 20;

	fahr = lower;
	while (fahr <= upper) {
		printf("%3.0f %6.1f\n", fahr, celcius(fahr));
		fahr = fahr + step;
	}
}
