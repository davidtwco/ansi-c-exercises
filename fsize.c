#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <pwd.h>

#define MAX_PATH 1024

#ifndef DIRSIZ
#define DIRSIZ 14
#endif

void dirwalk( char *dir,void (*fcn)(char *)) {
    char name[MAX_PATH];
    struct dirent *dp;
    DIR *dfd;

    if ((dfd = opendir(dir)) == NULL) {
        puts("error: cannot open directory");
        return;
    }

    puts(dir);

    // get each dir entry.
    while ((dp = readdir(dfd)) != NULL) {
        // skip . and .. are redundant.
        if (strcmp(dp->d_name, ".") == 0
                || strcmp(dp->d_name, "..") == 0)
            continue;
        if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
            puts("error: name too long!");
        else {
            sprintf(name, "%s/%s", dir, dp->d_name);
            // call fsize
            (*fcn)(name);
        }
    }
    closedir(dfd);
}

void fsize(char *name) {
    struct stat stbuf;

    if (stat(name, &stbuf) == -1) {
        puts("error: cannot get file stats");
        return;
    }

    if ((stbuf.st_mode & S_IFMT) == S_IFDIR){
        dirwalk(name, fsize);
    }
    struct passwd *pwd = getpwuid(stbuf.st_uid);
    // print file name, size and owner.
    printf("%81d %s owner: %s\n",(int)stbuf.st_size,name,pwd->pw_name);
}




int main(int argc,char *argv[]){

    if(argc==1)
        fsize(".");
    else
        while(--argc>0)
            fsize(*++argv);
    return 0;
}
