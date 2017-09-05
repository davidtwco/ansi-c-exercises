#include <math.h>
#include <stdio.h>
#include <stdlib.h> /* for atof() */

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

int getop(char[]);
void duplicate(void);
void swap(void);
void printTopOfStack(void);
void push(double);
double pop(void);

/* must compile with 'gcc calculator.c -lm -o a.out' */

/* reverse Polish calculator */
int main() {
    int type, previousType;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case 't':
                printTopOfStack();
                break;
            case 's':
                swap();
                printf("swapped\n\n");
                break;
            case 'd':
                duplicate();
                printf("duplicated\n\n");
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero division\n");
                break;
            case '%':
                op2 = pop();
                if (op2 != 0.0) {
                    int r = fmod(pop(), op2);
                    push((r * op2 < 0) ? r + op2 : r);
                } else
                    printf("error: cannot mod by zero");
                break;
            case '\n':
                if (previousType != 't' && previousType != 's' && previousType != 'd')
                    printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
        previousType = type;
    }
    return 0;
}

#define MAXVAL 100 /* maximum depth of val stack */

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

/* print: print top two elements of stack */
void printTopOfStack(void) {
    if (sp < 1) { /* need minimum of two elements */
        printf("not enough elements\n");
        return;
    }
    char s[80];

    sprintf(s, "top: %f", val[sp - 1]);
    printf("%s\n\n", s);
}

/* swap: swap top two stack elements */
void swap(void) {
    if (sp < 2) { /* need minimum of two elements */
        printf("not enough elements\n");
        return;
    }

    double temp = val[sp - 1];
    val[sp - 1] = val[sp - 2];
    val[sp - 2] = temp;
}

/* duplicate: duplicate the stack */
void duplicate(void) {
    int j, t = sp;
    for (j = 0; j < t; j++)
        push(val[j]);
}

/* push: push f onto value stack */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char s[]) {
    int i, c;

    i = 0;
    while ((s[i] = c = getch()) == ' ' || c == '\t')
        ;

    if (!isdigit(c) && c != '-' && c != '.')
        return c; /* not a number */

   if(c == '-') {
       int temp = getch();

       if (!isdigit(temp)) {
           ungetch(temp);
           return c; /* not a number */
       }

       c = temp;
       s[++i] = c;
   }

    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;

    if (c == '.') /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;

}

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch(void) { /* get a (possibly pushed back) character */
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) { /* push character back on input */
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

