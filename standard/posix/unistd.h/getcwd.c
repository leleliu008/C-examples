#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
	char buff[4098];
	char *str1 = getcwd(buff, sizeof(buff));
	printf("current working dir is %s\n", str1);
	
	char *str2 = getcwd(NULL, 0);
	if(NULL != str2) {
		printf("current working dir is %s\n", str2);
		free(str2);
	}

	return 0;
}
