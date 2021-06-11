typedef union {
	int a;
	char b;
} XX;

#include<stdio.h>
#include<stdlib.h>

int main() {
	XX x;
	x.a = 65;

	XX y = x;

	XX *z = (XX *)malloc(sizeof(XX));
	if(NULL != z) {
		(*z).b = 'a';
	}

	printf("x.a = %d\n", x.a);
	printf("x.b = %c\n", x.b);
	printf("-------------\n");
	printf("y.a = %d\n", y.a);
	printf("y.b = %c\n", y.b);
	
	if(NULL != z) {
		printf("-------------\n");
		printf("z->a = %d\n", z->a);
		printf("z->b = %c\n", z->b);
	
		free(z);
	}

	return 0;
}
