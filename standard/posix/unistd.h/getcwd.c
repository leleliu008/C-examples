#include<stdio.h>

#include<unistd.h>
#include<limits.h>

int main(int argc, char *argv[]) {
    char buff[PATH_MAX];

    const char * cwd = getcwd(buff, PATH_MAX);

    if (cwd == NULL) {
        perror(NULL);
        return 1;
    } else {
        printf("current working dir is %s\n", cwd);
        return 0;
    }
}
