#include<assert.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char *argv[]) {
	int i = 0;

	assert(atoi(argv[1]));

	printf("assert success\n");
	
	return 0;
}
