#include<stdlib.h>
#include<stdio.h>

int main() {
	printf("PWD = %s\n", getenv("PWD"));
	
	if(0 != setenv("PWD", "/", 1)) {
		perror("setenv fail!");
	}
	printf("PWD = %s\n", getenv("PWD"));
	
	if(0 != setenv("PWD", "/home", 0)) {
		perror("setenv fail!");
	}
	printf("PWD = %s\n", getenv("PWD"));
	
	return 0;
}
