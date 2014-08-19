#include<stdio.h>
#include<stdlib.h>

int main() {
	printf("NULL = %p\n", NULL);
	printf("EXIT_FAILURE = %d\n", EXIT_FAILURE);
	printf("EXIT_SUCCESS = %d\n", EXIT_SUCCESS);
	printf("RAND_MAX = %d\n", RAND_MAX);
	printf("MB_CUR_MAX = %d\n", (int)MB_CUR_MAX);
	return 0;
}
