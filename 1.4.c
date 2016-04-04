#include <stdio.h>

/* print Celsius-Fahrenheit table */

void print_heading()
{
    char *c = "celsius";
    char *f = "fahr";
    printf("%3s %3s\n", c, f);
}

void print_table() 
{
    float celsius, fahr;
    int lower, upper, step;

    lower = 0;
    upper = 100;
    step = 5;

    celsius = lower;

    while (celsius <= upper) {
	fahr = (celsius / (5.0/9.0)) + 32.0;
        printf("%6.1f %3.0f\n", celsius, fahr);
	celsius = celsius + step;
    }
}

main()
{
    print_heading();
    print_table();
}
