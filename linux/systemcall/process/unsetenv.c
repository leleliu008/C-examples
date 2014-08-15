#include<stdlib.h>
#include<stdio.h>

int main() {
	printf("PWD = %s\n", getenv("PWD"));

	if(0 != unsetenv("PWD")) {
		perror("unsetenv fail!");
	}
	printf("PWD = %s\n", getenv("PWD"));

	return 0;
}
