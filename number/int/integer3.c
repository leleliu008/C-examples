#include<stdio.h>

int main() {
	unsigned int a = -10;

	if(a > 0) {
		printf("%d\n", a);
		printf("%u\n", a);
	}

	unsigned int b = 10;

	if(b - 12 > 0) {
		printf("%d\n", b - 12);
		printf("%u\n", b - 12);
	}
	
	return 0;
}
