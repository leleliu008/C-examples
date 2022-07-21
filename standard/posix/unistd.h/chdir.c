#include<stdio.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: %s <DIR>\n", argv[0]);
		return 1;
	}

	char buff[1024] = {0};
	getcwd(buff, sizeof(buff));

	printf("current working dir is %s\n", buff);
	printf("change dir to %s\n", argv[1]);

	if (chdir(argv[1]) == 0) {
        memset(buff, 0, 1024);
		getcwd(buff, sizeof(buff));
		printf("current working dir is %s\n", buff);
	    return 0;
	} else {
		perror(argv[1]);
        return 1;
	}
}
