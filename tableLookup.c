#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist { /* table entry */
    struct nlist *next; /* next entry in chain */
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

/* example from Ch 6, Sec 6.6, Pg 144, 145 */

int main() {
}

unsigned hash(char *s);
struct nlist *lookup(char *s);
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
