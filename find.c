#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct file {
    FILE *fp;
    char *name;
    struct file *next;
};

struct file *getinput(int, char**);
void find(char *pattern, int number, int except, struct file *p);

/* find: print lines that match pattern from 1st arg */
int main(int argc, char *argv[]) {
    int c, except = 0, number = 0;
    struct file *p;

    while (--argc > 0 && (*++argv)[0] == '-')
        while ((c = *++argv[0]))
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default:
                    printf("find: illegal option %c\n", c);
                    argc = 0;
                    break;
            }

    if (argc < 1)
        printf("Usage: find -x -n [FILE]... pattern\n");
    else {
        p = getinput(argc, argv);
        find(argv[argc-1], number, except, p);
    }
    exit(0);
}

#define MAXLEN 1000

struct file *getfile(char *, struct file *);
struct file *falloc(void);

struct file *getinput(int argc, char *argv[]) {
    struct file *head, *p, *aux;

    aux = NULL;
    if (argc > 1) { /* if we are given filenames */
        do {
            head = getfile(*argv++, aux);
            argc--;
        } while (argc > 1 && head == NULL);
        aux = head;
        while (argc-- > 1)
            if ((p = getfile(*argv++, aux)) != NULL)
                aux = p;
    } else {
        if ((head = falloc()) != NULL) {
            head->fp = stdin;
            head->name = "input";
            head->next = NULL;
        }
    }

    return head;
}

/* getfile: with a file name tries to open the file and creates a node with a
 *          pointer to it and its name. */
struct file *getfile(char *filename, struct file *aux) {
    FILE *file;
    struct file *p;

    p = NULL;
    if ((file = fopen(filename, "r")) != NULL) {
        if ((p = falloc()) != NULL) {
            p->fp = file;
            p->name = filename;
            p->next = NULL;
            if (aux != NULL)
                aux->next = p;
        }
    } else
        fprintf(stderr, "error: cannot open file %s\n", filename);
    return p;
}

/* falloc: allocates a new struct file node and returns a pointer to it. */
struct file *falloc(void) {
    return (struct file *)malloc(sizeof(struct file));
}

/* find: searches the pattern in the list of structures starting from head. */
void find(char *pattern, int number, int except, struct file *p) {
    char line[MAXLEN];
    long lineno;
    int showFilename;

    while (p != NULL) {
        lineno = 0;
        showFilename = 1;

        while (fgets(line, MAXLEN, p->fp) != NULL) {
            lineno++;

            if ((strstr(line, pattern) != NULL) != except) {
                if (showFilename) {
                    printf("%s:\n", p->name);
                    showFilename = 0;
                }
                if (number)
                    printf("%ld: ", lineno);
                printf("%s", line);
            }
        }

        if (!showFilename)
            printf("\n");
        fclose(p->fp);
        p = p->next;
    }
}
