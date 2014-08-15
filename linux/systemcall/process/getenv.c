#include<stdlib.h>
#include<stdio.h>

int main() {
	char *value;
	
	value = getenv("HOME");
	printf("HOME = %s\n", value);
	
	value = getenv("PWD");
	printf("PWD = %s\n", value);
	
	return 0;
}
