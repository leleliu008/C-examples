typedef union {
	int a;
	char b;
} XX;


#include<stdio.h>

int main() {
	printf("sizeof(XX) = %lu\n", sizeof(XX));

	return 0;
}
