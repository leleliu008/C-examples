#include<stdio.h>

int main() {
	if(-1 == putc('#', stdout)) {
		perror("fputc error!");
	}
	printf("\n");
	return 0;
}
