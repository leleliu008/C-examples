#include<stdio.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: %s <DIR>\n", argv[0]);
		return 1;
	}

    const char * cwd = NULL;

    for (int length = 100; cwd == NULL; length += 100) {
        char buff[length];
        memset(buff, 0, length);
        cwd = getcwd(buff, length);
    }

    printf("current working dir is %s\n", cwd);
	printf("change  working dir to %s\n", argv[1]);

	if (chdir(argv[1]) == 0) {
        const char * cwd = NULL;

        for (int length = 100; cwd == NULL; length += 100) {
            char buff[length];
            memset(buff, 0, length);
            cwd = getcwd(buff, length);
        }

        printf("current working dir is %s\n", cwd);
	    return 0;
	} else {
		perror(argv[1]);
        return 1;
	}
}
