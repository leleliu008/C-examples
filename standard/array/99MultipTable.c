#include<stdio.h>

#define MAX 10

int main() {
	int i, j;
	for(i = 1; i < MAX; i++) {
		for(j = 1; j <= i; j++) {
			printf("%dx%d=%-2d ", i, j, i*j);
		}
		printf("\n");
	}
	return 0;
}
