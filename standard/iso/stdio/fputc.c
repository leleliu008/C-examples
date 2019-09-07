#include<stdio.h>

int main() {
	if(-1 == fputc('#', stdout)) {
		perror("fputc error!");
	}
	printf("\n");
	return 0;
}
