#include<unistd.h>
#include<stdio.h>

int main() {
	/* 环境变量 */
	extern char **environ;
	int i;
	for(i = 0; i < 10; i++) {
		printf("%s\n", *(environ + i));
	}
	
	return 0;
}
