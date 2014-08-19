#include<stdlib.h>
#include<stdio.h>

int main() {
	printf("PWD = %s\n", getenv("PWD"));

	if(0 != putenv("PWD=/")) {
		perror("putenv error!");
	}

	printf("PWD = %s\n", getenv("PWD"));
	return 0;
}
