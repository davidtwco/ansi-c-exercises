#include<stdio.h>

void escape(char s[], char t[]);
void unescape(char s[], char t[]);

int main() {
    char original[50] = "\aHello,\n\tWorld! Mistakee\b was \"Extra 'e'\"!\n";
    char escaped[51];

    escape(escaped, original);
    printf("escaped: %s\n", escaped);
    unescape(original, escaped);
    printf("unescaped: %s\n", original);

    return 0;
}

void escape(char s[], char t[]) {
    int i, j;

    i = j = 0;
    while (t[i]) {
        switch (t[i]) {
            case '\t':
                s[j++] = '\\';
                s[j++] = 't';
                break;
            case '\n':
                s[j++] = '\\';
                s[j++] = 'n';
                break;
            case '\a':
                s[j++] = '\\';
                s[j++] = 'a';
                break;
            case '\b':
                s[j++] = '\\';
                s[j++] = 'b';
                break;
            case '\r':
                s[j++] = '\\';
                s[j++] = 'r';
                break;
            case '\\':
                s[j++] = '\\';
                s[j++] = '\\';
                break;
            case '\"':
                s[j++] = '\\';
                s[j++] = '"';
                break;
            case EOF:
                s[j] = EOF;
                return;
            default:
                s[j++] = t[i];
                break;
        }

        ++i;
    }
}

void unescape(char s[], char t[]) {
    int i, j;

    i = j = 0;
    while (t[i]) {
        switch (t[i]) {
            case '\\':
                switch (t[++i]) {
                    case 't':
                        s[j++] = '\t';
                        break;
                    case 'n':
                        s[j++] = '\n';
                        break;
                    case 'a':
                        s[j++] = '\a';
                        break;
                    case 'b':
                        s[j++] = '\b';
                        break;
                    case 'r':
                        s[j++] = '\r';
                        break;
                    case '\\':
                        s[j++] = '\\';
                        break;
                    case '"':
                        s[j++] = '\"';
                        break;
                    case EOF:
                        s[j] = EOF;
                        return;
                    default:
                        s[j++] = t[i];
                        break;
                }
                break;
            default:
                s[j++] = t[i];
                break;
        }

        ++i;
    }
}
