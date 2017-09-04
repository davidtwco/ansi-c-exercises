#include <ctype.h>
#include <stdio.h>

double atof (char s[]);

int main() {
    char test1[] = "123.45e-6";
    char test2[] = "123.45e6";
    char test3[] = "-123.45e-6";
    char test4[] = "-123.45e6";

    printf("%s as double: %g\n",
           test1, atof(test1));

    printf("%s as double: %g\n",
           test2, atof(test2));

    printf("%s as double: %g\n",
           test3, atof(test3));

    printf("%s as double: %g\n",
           test4, atof(test4));

    return 0;
}

/* atof: convert string s to double */
double atof (char s[]) {
    double val, power;
    int i, j, sign;
    int exponent, exponentSign;


    for (i = 0; isspace(s[i]); i++) /* skip whitespace */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    if (s[i] == 'e' || s[i] == 'E')
        i++;

    /* we can get the exponent sign in the same way as
     * the normal sign */
    exponentSign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    /* we can also get the exponent values in the same
     * way as the normal values */
    for (exponent = 0.0; isdigit(s[i]); i++)
        exponent = 10.0 * exponent + (s[i] - '0');

    /* the exponent is how many times we should
     * multiply or divide (depending on the sign)
     * by 10. Therefore, we loop 'exponent' times
     * and if the sign is negative we multiply
     * the power by 10 (since the power then goes
     * on to be the denominator, this achieves
     * further division, as intended). Similarly,
     * we divide by 10 when the sign is positive. */
    for (j = 0; j < exponent; j++)
        if (exponentSign == -1)
            power *= 10.0;
        else
            power /= 10.0;

    return sign * val / power;
}
