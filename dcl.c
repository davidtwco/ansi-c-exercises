#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };
enum { ERR_YES, ERR_NO };

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype; /* type of last token */
char token[MAXTOKEN]; /* last token string */
char name[MAXTOKEN]; /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc. */
char out[1000]; /* output string */
int errtoken = ERR_NO;

/* example from Ch 5, Sec 5.12, Pg 123-125 */

int main() { /* convert declaration to words */
    while (gettoken() != EOF) { /* 1st token on line */
        strcpy(datatype, token); /* is the datatype */
        out[0] = '\0';
        dcl(); /* parse rest of line */
        if (tokentype != '\n')
            printf("syntax error\n");
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

/* dcl: parse a declarator */
void dcl(void) {
    int ns;

    for (ns = 0; gettoken() == '*'; ) /* count *'s */
        ns++;
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

void paramdcl(void);

/* dirdcl: parse a direct declarator */
void dirdcl(void) {
    int type;

    if (tokentype == '(') { /* dcl */
        dcl();
        if (tokentype != ')') {
            printf("missing )\n");
            errtoken = ERR_YES;
        }
    } else if (tokentype == NAME) /* variable name */
        strcpy(name, token);
    else {
        printf("error: expected name or (dcl)\n");
        errtoken = ERR_YES;
    }

    while ((type=gettoken()) == PARENS || type == BRACKETS || type == '(')
        if (type == PARENS)
            strcat(out, " function returning");
        else if (type == '(') {
            strcat(out, " function expecting");
            paramdcl();
            strcat(out, " and returning");
        } else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
}

void dclspec(void);

void paramdcl(void) {
    do {
        dclspec();
    } while (tokentype == ',');

    if (tokentype != ')')
        printf("error: missing ) in parameter declaration");
}

int typespecifier(void);
int typequalifier(void);

void dclspec(void) {
    char temp[MAXTOKEN];
    temp[0] = '\0';
    gettoken();

    do {
        if (tokentype != NAME) {
            errtoken = ERR_YES;
            dcl();
        } else if (typespecifier() || typequalifier()) {
            strcat(temp, " ");
            strcat(temp, token);
            gettoken();
        } else {
            printf("error: unknown type in param list\n");
            errtoken = ERR_YES;
        }
    } while (tokentype != ',' && tokentype != ')');

    strcat(out, temp);
    if (tokentype == ',')
        strcat(out, ",");
}

int compare(const void *s, const void *t);

int typespecifier(void) {
    static char *type[] = { "char", "int", "void" };
    char *pt = token;

    if (bsearch(&pt, type, sizeof(type)/sizeof(char *), sizeof(char *), compare) == NULL)
        return 0;
    return 1;
}

int typequalifier(void) {
    static char *type[] = { "const", "volatile" };
    char *pt = token;

    if (bsearch(&pt, type, sizeof(type)/sizeof(char *), sizeof(char *), compare) == NULL)
        return 0;
    return 1;
}

int compare(const void *s, const void *t) {
    char **chs;
    char **cht;
    chs = (char **) s;
    cht = (char **) t;
    return strcmp(*chs, *cht);
}

int getch(void);
void ungetch(int);

int gettoken(void) {
    int c;
    char *p = token;

    if (errtoken == ERR_YES) {
        errtoken = ERR_NO;
        return tokentype;
    }

    while ((c = getch()) == ' ' || c == '\t')
        ;

    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; )
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); )
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    }

    return tokentype = c;
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
