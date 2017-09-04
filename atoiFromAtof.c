#include <ctype.h>

/* example from Ch 4, Sec 4.2, Pg 73 */
/* atoi: convert string s to integer using atof */
int atoi(char s[]) {
    double atof(char s[]);

    return (int) atof(s);
}

/* taken from example in Ch 4, Sec 4.2, Pg 71 */
/* atof: convert string s to double */
double atof (char s[]) {
    double val, power;
    int i, sign;


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
    return sign * val / power;
}
