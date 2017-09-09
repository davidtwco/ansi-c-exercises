#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> /* for atof() */

#define MAXOP 100 /* max size of operand or operator */
#define MAXVARS 26 /* number of variables */
#define MAXLINE 1000 /* max line length */
#define NUMBER 'N' /* signal that a number was found */
#define FUNCTION 'F' /* signal that a number was found */
#define VARIABLE 'V' /* signal that a variable was found */

void callFunc(char funcName[]);
int getop(char[]);
void duplicate(void);
void swap(void);
void printTopOfStack(void);
void push(double d);
void pushv(char f[]);
double pop(void);
char* popv(void);

int _getline(char line[], int maxline);

/* must compile with 'gcc calculator.c -lm -o a.out' */

char line[MAXLINE];
int lp;
double vars[MAXVARS];

/* reverse Polish calculator */
int main(int argc, char *argv[]) {
    int i, type;
    double op2;
    char s[MAXOP];

    if (argc <= 1) {
        printf("error: need more than 1 argument\n");
        return 1;
    }

    lp = 0;
    while(--argc > 0) {
        char temp[MAXLINE];
        sprintf(temp, "%s%s", *++argv, (argc > 1) ? " " : "");
        strcat(line, temp);
    }
    strcat(line, "\n");

    /* We set all our variables to zero as a default value to
     * avoid any issues when accessing variables that are not
     * explicitly set. */
    printf("all variables are set to zero by default\n");
    for (i = 0; i < MAXVARS; ++i)
        vars[i] = 0;

    while ((type = getop(s)) != '\0') {
        switch (type) {
            case NUMBER:
                pushv(s);
                break;
            case FUNCTION:
                callFunc(s);
                printTopOfStack();
                break;
            case VARIABLE:
                pushv(s);
                break;
            case 'q':
                return 0;
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
                printf("error: unknown command type: \"%c\", inpt: \"%s\"\n",
                       type, s);
                break;
        }
    }
    return 0;
}

void callFunc(char funcName[]) {
    double op2;
    char vop2[MAXOP];

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
    else if (strcmp(funcName, "set") == 0) {
        /* We pop both our operands, validate their types and
         * set the corresponding index for our variable in the
         * vars array. */
        strcpy(vop2, popv());
        op2 = pop();

        if (!isalpha(vop2[0])) {
            printf("error: second argument must be variable\n");
        } else {
            int index = vop2[0] - 'a';
            vars[index] = op2;

            printf("set var \"%c\" to \"%g\", pushing \"%c\" onto stack\n",
                   vop2[0], op2, vop2[0]);

            pushv(vop2);
        }
    } else
        printf("error: unknown function %s\n", funcName);
}

#define MAXVAL 100 /* maximum depth of val stack */

int sp = 0; /* next free stack position */
char val[MAXOP][MAXVAL]; /* value stack */

/* print: print top two elements of stack */
void printTopOfStack(void) {
    if (sp < 1) { /* need minimum of two elements */
        printf("not enough elements\n");
        return;
    }

    printf("\t%s\n", val[sp - 1]);
}

/* swap: swap top two stack elements */
void swap(void) {
    if (sp < 2) { /* need minimum of two elements */
        printf("not enough elements\n");
        return;
    }

    char temp[MAXOP];
    strcpy(temp, val[sp - 1]);
    strcpy(val[sp - 1], val[sp - 2]);
    strcpy(val[sp - 2], temp);
    printf("swapped\n\n");
}

/* duplicate: duplicate the stack */
void duplicate(void) {
    int j, t = sp;
    for (j = 0; j < t; j++)
        pushv(val[j]);
    printf("duplicated\n\n");
}

/* push: push number d onto value stack */
void push(double d) {
    char temp[MAXOP];
    if (sp < MAXVAL) {
        sprintf(temp, "%g", d);
        pushv(temp);
    } else
        printf("error: stack full, can't push %g\n", d);
}

/* pushv: push variable or number f onto value stack */
void pushv(char f[]) {
    if (sp < MAXVAL)
        strcpy(val[sp++], f);
    else
        printf("error: stack full, can't push %s\n", f);
}

/* pop: pop and return top value from stack as number */
double pop(void) {
    char r[MAXOP];
    if (sp > 0) {
        strcpy(r, val[--sp]);
        /* If we pop a variable, find its numeric value. */
        if (isalpha(r[0]))
            return vars[r[0] - 'a'];
        else
            return atof(r);
    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* popv: pop and return top value from stack as number or variable */
char* popv(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return "0.0";
    }
}

/* getop: get next operator or numeric operand */
int getop(char s[]) {
    int i, c;

    i = 0;
    /* skip any whitespace, keep last character
     * (since it will not be whitespace) for
     * later processing */
    while ((s[i] = c = line[lp++]) == ' ' || c == '\t')
        ;

    /* if it was a letter, process as func name. */
    if (isalpha(c)) {
        int temp = line[lp];

        /* if not followed by another letter then it
         * is a variable name */
        if (!isalpha(temp)) {
            s[++i] = '\0';
            return VARIABLE;
        }

        while (isalpha(s[++i] = c = line[lp++]))
            ;
        s[i] = '\0';
        return FUNCTION;
    }

    /* if it was a '-' then check if it is a minus operator
     * or a negative number */
    if(c == '-') {
        int temp = line[lp];

        /* it is a operator */
        if (!isdigit(temp)) {
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
        while (isdigit(s[++i] = c = line[lp++]))
            ;

    /* collect fraction part */
    if (c == '.')
        while (isdigit(s[++i] = c = line[lp++]))
            ;

    s[i] = '\0';
    lp--;
    return NUMBER;
}
