#include<stdlib.h>
#include<stdio.h>

int main() {
	printf("It's about to abort!\n");
	abort();
	printf("This is never reached!\n");

	return 0;
}
