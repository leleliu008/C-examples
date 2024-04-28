#include<stdio.h>
#include<string.h>

#include<unistd.h>
#include<limits.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: %s <DIR>\n", argv[0]);
		return 1;
	}

    char buff[PATH_MAX];
    const char * cwd = getcwd(buff, PATH_MAX);

    if (cwd == NULL) {
        perror(NULL);
        return 1;
    }

    printf("current working dir is %s\n", cwd);
	printf("change  working dir to %s\n", argv[1]);

	if (chdir(argv[1]) == 0) {
        char buff[PATH_MAX];
        const char * cwd = getcwd(buff, PATH_MAX);

        if (cwd == NULL) {
            perror(NULL);
            return 1;
        }

        printf("current working dir is %s\n", cwd);
	    return 0;
	} else {
		perror(argv[1]);
        return 1;
	}
}
