#include<stdio.h>

#define MAX(a, b) a > b ? a : b

int main() {
	int max = MAX(3, 4);
	printf("max = %d", max);
	return 0;
} 
