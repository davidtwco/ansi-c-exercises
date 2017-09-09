#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000
#define BUFSIZE 100
#define NUMBER '0'

/* This file contains programs from previous chapters (before Ch 5)
 * that have been converted to use pointers instead of subscript indexing
 * for Ex 5-6. */

int _atoi(char *s);
double _atof (char *s);
void itoa(int n, char *s);
void itoaFieldWidth(int n, char s[], int fw);
void itob(int n, char *s, int b);
void reverse(char *s);
int _getline(char *s, int lim);
int strindex(char *s, char *t);
int getop (char *str);

int main() {
    char *s = "9238";
    char *t = "-273";

    printf("[atoi] '%s' as int: %d\n", s, atoi(s));
    printf("[atoi] '%s' as int: %d\n\n", t, atoi(t));

    signed largest = INT_MIN;
    char largestString[MAX_SIZE];

    itoa(largest, largestString);
    printf("[itoa, reverse] %d as string: %s\n\n", largest, largestString);

    int value = 14;
    char valueString[MAX_SIZE];

    itob(value, valueString, 10);
    printf("[itob] %d (base 10) as string: %s\n", value, valueString);

    itob(value, valueString, 2);
    printf("[itob] %d (base 2) as string: %s\n", value, valueString);

    itob(value, valueString, 8);
    printf("[itob] %d (base 8) as string: %s\n", value, valueString);

    itob(value, valueString, 16);
    printf("[itob] %d (base 16) as string: %s\n", value, valueString);

    itob(largest, largestString, 10);
    printf("[itob] %d (base 10) as string: %s\n", largest, largestString);

    itob(largest, largestString, 2);
    printf("[itob] %d (base 2) as string: %s\n", largest, largestString);

    itob(largest, largestString, 8);
    printf("[itob] %d (base 8) as string: %s\n", largest, largestString);

    itob(largest, largestString, 16);
    printf("[itob] %d (base 16) as string: %s\n\n", largest, largestString);

    char line[MAX_SIZE];
    printf("[getline] type a line..\n");
    _getline(line, MAX_SIZE);
    printf("[getline] new line: %s\n", line);

    char test1[] = "123.45e-6";
    char test2[] = "123.45e6";
    char test3[] = "-123.45e-6";
    char test4[] = "-123.45e6";

    printf("[atof] %s as double: %g\n",
           test1, atof(test1));

    printf("[atof] %s as double: %g\n",
           test2, atof(test2));

    printf("[atof] %s as double: %g\n",
           test3, atof(test3));

    printf("[atof] %s as double: %g\n\n",
           test4, atof(test4));

    signed normal = -283819;
    char normalString[MAX_SIZE];

    itoaFieldWidth(normal, normalString, 24);
    printf("[itoaFieldWidth] %d as string: %s\n\n", normal, normalString);

    char line1[] = "this is text";
    char line2[] = "is";

    printf("[strindex] index of '%s' in '%s': %d\n\n",
           line2, line1, strindex(line1, line2));

    char inpt[BUFSIZE];
    int type;

    printf("[getop] type input for getop\n");
    while ((type = getop(inpt)) != EOF) {
        switch (type) {
            case NUMBER:
                printf ("[getop] found number: %s\n", inpt);
                break;
            case '+':
                printf ("[getop] found \'+\'\n");
                break;
            case '\n':
                printf ("[getop] found newline\n");
                break;
            default:
                printf ("found something else: %s\n", s);
                break;
        }
    }

    return 0;
}

/* atoi: convert s to integer */
int _atoi(char *s) {
    int n, sign;

    while (isspace(*s)) /* skip white space */
        s++;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-') /* skip sign */
        s++;
    n = 0;
    while (isdigit(*s)) {
        n = 10 * n + (*s - '0');
        s++;
    }
    return sign * n;
}

/* atof: convert string s to double */
double _atof (char *s) {
    double val, power;
    int j, sign;
    int exponent, exponentSign;


    for (; isspace(*s); s++) /* skip whitespace */
        ;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')
        s++;
    for (val = 0.0; isdigit(*s); s++)
        val = 10.0 * val + (*s - '0');
    if (*s == '.')
        s++;
    for (power = 1.0; isdigit(*s); s++) {
        val = 10.0 * val + (*s - '0');
        power *= 10.0;
    }
    if (*s == 'e' || *s == 'E')
        s++;

    /* we can get the exponent sign in the same way as
     * the normal sign */
    exponentSign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')
        s++;
    /* we can also get the exponent values in the same
     * way as the normal values */
    for (exponent = 0.0; isdigit(*s); s++)
        exponent = 10.0 * exponent + (*s - '0');

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

/* itoa: convert n to characters in s */
void itoa(int n, char *s) {
    char *o = s;
    int sign = n;

    do { /* generate digits in reverse order */
        *s = abs(n % 10) + '0'; /* get next digit */
        s++;
    } while (n /= 10); /* delete it */
    if (sign < 0) {
        *s = '-';
        s++;
    }
    *s = '\0';
    reverse(o);
}

/* itoaFieldWidth: convert n to characters in s, padded by fw */
void itoaFieldWidth(int n, char s[], int fw) {
    char *o = s;
    int  j, req, sign;
    sign = n;

    do { /* generate digits in reverse order */
        *s = abs(n % 10) + '0'; /* get next digit */
        s++;
    } while (n /= 10); /* delete it */

    /* Before we add a sign, add any required padding characters.
     * After reversal, will end up on the left, as required. */
    req = fw - (s - o) - ((sign < 0) ? 1 : 0);
    for (j = 0; j < req; j++){
        *s = '0';
        s++;
    }

    if (sign < 0) {
        *s = '-';
        s++;
    }

    *s = '\0';
    reverse(o);
}

/* itob: convert n in base b to characters in s */
void itob(int n, char *s, int b) {
    char *o = s;
    int j, sign;
    sign = n;

    do { /* generate digits in reverse order */
        j = abs(n % b); /* get next digit */
        *s = j + ((j > 9) ? 'A' - 10 : '0');
        s++;
    } while (n /= b); /* delete it */
    if (sign < 0) {
        *s = '-';
        s++;
    }
    *s = '\0';
    reverse(o);
}

/* reverse: reverse string s in place */
void reverse(char *s) {
    char *t = s + strlen(s) - 1;
    int c;

    while (s < t) {
        c = *s;
        *s = *t;
        *t = c;

        s++;
        t--;
    }
}

/* getline:  get line into s, return length */
int _getline(char *s, int lim)
{
    int c;
    char *o = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';

    return s - o;
}

/* strindex: get index of t in s */
int strindex(char *s, char *t) {
    char *sb = s;
    char *ss, *tb;

    while (*sb) {
        tb = t;  /* Reset the pointer to the beginning of the string. */
        ss = sb; /* Reset the substring pointer to the base string
                  * pointer. */
        while (*tb != '\0' && *ss == *tb) {

            if (*(tb+1) == '\0' && (tb - t) > 0) {
                return sb - s;
            }

            ss++;
            tb++;
        }

        sb++;
    }
    return -1;
}

int getch (void);
void ungetch (int c);

int getop (char *str) {
    int c;
    while ((*str++ = c = getch()) == ' ' || c == '\t')
        ;

    *str = '\0';
    if (!isdigit(c) && c != '.')
        return c;

    if (isdigit(c))
        while (isdigit(*str++ = c = getch()))
            ;

    if (c == '.')
        while (isdigit(*str++ = c = getch()))
            ;

    *--str = '\0';
    if (c != EOF)
        ungetch(c);

    return NUMBER;
}

char buf[BUFSIZE];
int  bufp = 0;

int getch (void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch (int c) {
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters.\n");
    } else {
        buf[bufp++] = c;
    }
}
