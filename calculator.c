#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> /* for atof() */

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define FUNCTION 'F' /* signal that a number was found */

void callFunc(char funcName[]);
int getop(char[]);
void duplicate(void);
void swap(void);
void printTopOfStack(void);
void push(double);
double pop(void);

/* must compile with 'gcc calculator.c -lm -o a.out' */

/* reverse Polish calculator */
int main() {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case FUNCTION:
                callFunc(s);
                printTopOfStack();
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
                printTopOfStack();
                pop();
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}

void callFunc(char funcName[]) {
    int op2;

    if (strcmp(funcName, "sin") == 0)
        push(sin(pop()));
    else if (strcmp(funcName, "cos") == 0)
        push(cos(pop()));
    else if (strcmp(funcName, "tan") == 0)
        push(tan(pop()));
    else if (strcmp(funcName, "exp") == 0)
        push(exp(pop()));
    else if (strcmp(funcName, "log") == 0)
        push(log(pop()));
    else if (strcmp(funcName, "pow") == 0) {
        op2 = pop();
        push(pow(pop(), op2));
    }
    else if (strcmp(funcName, "sqrt") == 0)
        push(sqrt(pop()));
    else if (strcmp(funcName, "floor") == 0)
        push(floor(pop()));
    else if (strcmp(funcName, "ceil") == 0)
        push(ceil(pop()));
    else if (strcmp(funcName, "abs") == 0)
        push(fabs(pop()));
    else if (strcmp(funcName, "top") == 0)
        ; /* this is always called after function calls */
    else if (strcmp(funcName, "swap") == 0)
        swap();
    else if (strcmp(funcName, "duplicate") == 0)
        duplicate();
    else
        printf("error: unknown function %s\n", funcName);
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

    printf("\t%.8g\n", val[sp - 1]);
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
    printf("swapped\n\n");
}

/* duplicate: duplicate the stack */
void duplicate(void) {
    int j, t = sp;
    for (j = 0; j < t; j++)
        push(val[j]);
    printf("duplicated\n\n");
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
    /* skip any whitespace, keep last character
     * (since it will not be whitespace) for
     * later processing */
    while ((s[i] = c = getch()) == ' ' || c == '\t')
        ;

    /* if it was a letter, process as func name. */
    if (isalpha(c)) {
        int temp = getch();

        /* if not followed by another letter then it
         * is a operator */
        if (!isalpha(temp)) {
            ungetch(temp);
            return c;
        }

        ungetch(temp);
        while (isalpha(s[++i] = c = getch()))
            ;
        s[i] = '\0';
        return FUNCTION;
    }

    /* if it was a '-' then check if it is a minus operator
     * or a negative number */
    if(c == '-') {
        int temp = getch();

        /* it is a operator */
        if (!isdigit(temp)) {
            ungetch(temp);
            return c;
        }

        c = temp;
        s[++i] = c;
    }

    /* if it wasn't a func name or negative symbol or digit
     * then return it */
    if (!isdigit(c) && c != '.')
        return c;

    /* collect integer part */
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;

    /* collect fraction part */
    if (c == '.')
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

