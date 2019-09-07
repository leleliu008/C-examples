typedef union {
	int a;
	char b;
} XX;


#include<stdio.h>

int main() {
	XX x;
	
	x.a = 65;
	printf("x.a = %d\n", x.a);
	printf("x.b = %c\n", x.b);

	printf("-------------\n");

	x.b = 'a';

	printf("x.a = %d\n", x.a);
	printf("x.b = %c\n", x.b);

	return 0;
}
