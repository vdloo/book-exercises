#include <stdio.h>
#include <limits.h>
/* Note: these statement expression macros are not standard C99 but a GCC 
 * extension. You can write it out by hand but for the sake of brevity 
 * this bit of metaprogramming here will allow us to abstract some logic 
 * over variable types. To see what code is constructed when these macros
 * are expanded run "cpp 2.1.c" */
#define determine_limit(mutate, operator, upper) ({ \
    do { \
        previous = next; \
        next mutate 1; \
    } while (next operator previous); \
    upper = previous; \
})

#define determine_type_limits(type, upper, lower) ({ \
    type next = 0; \
    type previous = 0; \
    determine_limit(+=, >, upper); \
    determine_limit(-=-, <, lower); \
})

#define print_type_limit(type, message, specifier) ({ \
    type upper_limit, lower_limit; \
    determine_type_limits(type, upper_limit, lower_limit); \
    printf( \
        "%s range is "specifier" to "specifier"\n", \
        message, lower_limit, upper_limit \
    ); \
})

#define print_type_qualifications_limits(type, name, signed_specifier, \
        unsigned_specifier) ({ \
    printf("computed %s limits:\n", name); \
    print_type_limit(signed type, "Signed", signed_specifier); \
    print_type_limit(unsigned type, "Unsigned", unsigned_specifier); \
})

void lookup_limits()
{
    printf("limits.h char limits:\n");
    printf("Signed range is %d to %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("Unsigned range is 0 to %d\n", UCHAR_MAX);

    printf("limits.h short limits:\n");
    printf("Signed range is %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("Unsigned range is 0 to %d\n", USHRT_MAX);

    printf("limits.h int limits:\n");
    printf("Signed range is %d to %d\n", INT_MIN, INT_MAX);
    printf("Unsigned range is 0 to %u\n", UINT_MAX);

    printf("limits.h long limits:\n");
    printf("Signed range is %ld to %ld\n", LONG_MIN, LONG_MAX);
    printf("Unsigned range is 0 to %lu\n", ULONG_MAX);
}

void compute_limits()
{
    print_type_qualifications_limits(char, "char", "%d", "%d");
    print_type_qualifications_limits(short, "short", "%d", "%d");
    print_type_qualifications_limits(int, "int", "%d", "%u");
    print_type_qualifications_limits(long, "long", "%ld", "%lu");
}

int main(void)
{
    lookup_limits();
    printf("\n");
    compute_limits();
    return 0;
}

