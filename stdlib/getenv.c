#include<stdlib.h>
#include<stdio.h>

int main() {
	char *value;
	
	value = getenv("HOME");
	if(value) {
		printf("HOME = %s\n", value);
	}
	
	value = getenv("PWD");
	if(value) {
		printf("PWD = %s\n", value);
	}

	value = getenv("haha");
	if(value) {
		printf("haha = %s\n", value);
	} else {
		printf("haha = NULL\n");
	}

	return 0;
}
