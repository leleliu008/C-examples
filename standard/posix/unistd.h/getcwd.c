#include<stdio.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char *argv[]) {
    const char * cwd = NULL;

    for (int length = 100; cwd == NULL; length += 100) {
        char buff[length];
        memset(buff, 0, length);
        cwd = getcwd(buff, length);
    }

    printf("current working dir is %s\n", cwd);

	return 0;
}
