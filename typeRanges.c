#include <stdio.h>
#include <limits.h>
#include <float.h>

main() {
    /* Calculation of these limits from direct
     * computation (as specified in exercise) is
     * omitted as there doesn't seem to be a way to
     * do this portably. */

    printf("bits of char: %d\n", CHAR_BIT);

    printf("char min: %d\n", CHAR_MIN);
    printf("char max: %d\n\n", CHAR_MAX);

    printf("int min: %d\n", INT_MIN);
    printf("int max: %d\n\n", INT_MAX);

    printf("long min: %ld\n", LONG_MIN);
    printf("long max: %ld\n\n", LONG_MAX);

    printf("signed char min: %d\n", SCHAR_MIN);
    printf("signed char max: %d\n\n", SCHAR_MAX);

    printf("short min: %d\n", SHRT_MIN);
    printf("short max: %d\n\n", SHRT_MAX);

    printf("unsigned char max: %u\n", UCHAR_MAX);
    printf("unsigned int max: %u\n", UINT_MAX);
    printf("unsigned long max: %lu\n", ULONG_MAX);
    printf("unsigned short max: %u\n\n", USHRT_MAX);

    printf("float min: %f\n", FLT_MIN);
    printf("float max: %f\n\n", FLT_MAX);

    printf("double min: %f\n", DBL_MIN);
    printf("double max: %f\n\n", DBL_MAX);

    printf("long double min: %Lf\n", LDBL_MIN);
    printf("long double max: %Lf\n\n", LDBL_MAX);

    return 0;
}
