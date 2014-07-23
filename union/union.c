union XX {
	int a;
	char b;
};


#include<stdio.h>

int main() {
	union XX x;
	
	x.a = 65;
	printf("x.a = %d\n", x.a);
	printf("x.b = %c\n", x.b);

	printf("-------------\n");

	x.b = 'a';

	printf("x.a = %d\n", x.a);
	printf("x.b = %c\n", x.b);

	return 0;
}
