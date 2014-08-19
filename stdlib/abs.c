#include<stdlib.h>
#include<stdio.h>

int main() {
	printf("abs(-5) = %d\n", abs(-5));
	printf("labs(-5L) = %ld\n", labs(-5L));
	printf("llabs(-5LL) = %lld\n", llabs(-5LL));

	return 0;
}
