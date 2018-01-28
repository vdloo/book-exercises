#include <stdio.h>

/* print reverse Fahrenheit-Celsius table */

void print_heading()
{
    char *f = "fahr";
    char *c = "celcius";
    printf("%3s %3s\n", f, c);
}

void print_table() 
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;
    
    fahr = upper;
    while (fahr >= lower) {
        celsius = (5.0/9.0) * (fahr-32.0);
        printf("%3.0f %6.1f\n", fahr, celsius);
	fahr = fahr - step;
    }
}

int main(void)
{
    print_heading();
    print_table();
    return 0;
}
