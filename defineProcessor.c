#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101
#define MAXWORD 1000

struct nlist { /* table entry */
    struct nlist *next; /* next entry in chain */
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

struct nlist *install(char *name, char *defn);
struct nlist *lookup(char *s);
int undef(char * name);

int preproc(void);
int backslash(void);
int comment(void);
int literal(void);
int readword(void);

int getch(void);
void ungetch(int c);

int main() {
    int c;
    int status = 1; /* 1 at line begin, 2 for failure, 0 otherwise */

    for (;;) {
        while(isspace(c = getch())) {
            putchar(c);
            if(c == '\n')
                status = 1;
        }

        if(c == '#' && status == 1)
            status = preproc();
        else if(c == '\\')
            status = backslash();
        else if(c == '/')
            status = comment();
        else if(c == '\"')
            status = literal();
        else if(c == EOF)
            return 0;
        else if(!isalpha(c) && c != '_') {
            putchar(c);
            status = 0;
        } else {
            ungetch(c);
            status = readword();
        }

        if(status == 2)
            return 1;
    }
    return 0;
}

/* preproc: When a '#' is found at the beginning of a line.
 *
 * If a #define statement is found, stores the search and replacement
 * text in the hash table. Else prints what was read.
 *
 * The line a #define statement is found on is replaced with a blank line. */
int preproc(void) {
    int c;
    char name[MAXWORD+1], defn[MAXWORD+1];
    char *n, *d;

    /* Read what comes after the '#' */
    for(n = name; isalpha(c = getch()) && n - name < MAXWORD; ++n)
        *n = c;
    *n = '\0';

    /* If it's a #define... */
    if(strcmp(name, "define") == 0) {

        /* Ignore whitespace. */
        while(isspace(c)) {
            if(c == '\n') { /* a #define followed by a '\n' is discarded */
                putchar(c);
                return 1;
            }
            c = getch();
        }

        /* Read search text */
        for(n = name; (isalnum(c) || c == '_') && n - name < MAXWORD; ++n) {
            *n = c;
            c = getch();
        }
        *n = '\0';

        /* Ignore whitespace. */
        while(isspace(c)) {
            if(c == '\n')
                *defn = '\0'; /* If there is no replacement text. */
            c = getch();
        }

        /* Read replacement text. */
        for(d = defn; (isalnum(c) || c == '_') && d - defn < MAXWORD; ++d) {
            *d = c;
            c = getch();
        }
        *d = '\0';

        /* Add to hash table. */
        if(install(name, defn) == NULL)
            return 2;
    } else { /* not a #define statement */
        putchar('#');
        printf("%s", name);
    }

    /* Finish line reading/printing line. */
    while(c != '\n') {
        if(c == EOF)
            return EOF;
        putchar(c);
        c = getch();
    }
    putchar(c);
    return 1;
}

/* backslash:  If a /, *, or " is preceded by a \ it is
 * just printed, not used in a comment or string literal. */
int backslash(void) {
    int c, slash = 1;

    putchar('\\');
    while((c = getch()) == '\\') {
        slash = !slash;
        putchar(c);
    }

    if(slash)
        putchar(c);
    else
        ungetch(c);

    return 0;
}

/* comment:  Prints comments. */
int comment(void) {
    int c, afterStar = 0;

    putchar('/');

    if((c = getch()) == '*') { /* Begin comment */
        putchar(c);
        c = getch();

        while (c != EOF) {
            if (c == '\\') {
                backslash();
                afterStar = 0;
            } else if (c == '*') {
                afterStar = 1;
                putchar(c);
            } else if (c == '/' && afterStar) {
                putchar(c);
                return 0;
            } else {
                afterStar = 0;
                putchar(c);
            }

            c = getch();
        }

        if(c == EOF)
            return EOF;

        putchar(c);
        return 0;
    } else {
        ungetch(c);
        return 0;
    }
}

/* literal:  Prints string literals.  */
int literal(void) {
    int c;
    putchar('\"');
    c = getch();

    while(c != '\"' && c != EOF) {
        if(c == '\\')
            backslash();
        else
            putchar(c);
        c = getch();
    }

    if(c == EOF)
        return EOF;

    putchar(c);
    return 0;
}

/* readword: Read an identifier and lookup the hash table.
 * If found, replace with the replacement text. Else, print. */
int readword(void) {
    int c;
    char word[MAXWORD];
    char *w;
    struct nlist *node;

    c = getch();
    for(w = word; (isalnum(c) || c == '_') && c != EOF; ++w) {
        *w = c;
        c = getch();
    }

    *w = '\0';
    node = lookup(word);

    if(node == NULL)
        printf("%s", word);
    else
        printf("%s", node->defn);

    if(c == EOF)
        return EOF;

    ungetch(c);
    return 0;
}

unsigned hash(char *s);
char *_strdup(char *s);

struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) { /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = _strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else /* already there */
        free((void *) np->defn); /* free previous defn */
    if ((np->defn = _strdup(defn)) == NULL)
        return NULL;
    return np;
}

int undef(char * name) {
    struct nlist * np1, * np2;

    /* If we don't find an existing record then there is
     * nothing to remove. */
    if ((np1 = lookup(name)) == NULL)
        return 1;

    /* Walk along the list, keeping track of the previous
     * record we had. */
    for (np1 = np2 = hashtab[hash(name)]; np1 != NULL;
         np2 = np1, np1 = np1->next ) {
        /* We found the record to remove */
        if (strcmp(name, np1->name) == 0) {

            /*  Remove node from list  */
            if (np1 == np2)
                /* If there was no previous record, ie. we're
                 * at the root of the table, then set the table
                 * pointer to np1's next. */
                hashtab[hash(name)] = np1->next;
            else
                /* Replace the previous node's next pointer
                 * (that was pointing at np1) to the record
                 * that np1's next pointer is pointing at. */
                np2->next = np1->next;

            /* Free up memory. */
            free(np1->name);
            free(np1->defn);
            free(np1);

            return 0;
        }
    }

    return 1; /* Name not found. */
}

/* hash: form hash value for string s */
unsigned hash(char *s) {
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s) {
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np; /* found */
    return NULL; /* not found */
}

char *_strdup(char *s) { /* make a duplicate of s */
    char *p;

    p = (char *) malloc(strlen(s) + 1); /* +1 for '\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
}

#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch() */
int bufp = 0;       /* next free position in buf */

int getch(void) { /* get a (possibly pushed back) character */
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {  /* push character back on input */
    if(bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
    return;
}
