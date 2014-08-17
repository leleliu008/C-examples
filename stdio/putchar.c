#include<stdio.h>

int main() {
	if(-1 == putchar('#')) {
		perror("fputc error!");
	}
	printf("\n");
	return 0;
}
