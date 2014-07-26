//数组的sizeof

#include<stdio.h>

void xx(char a3[4]) {
	printf("sizeof(a3) = %lu\n", sizeof(a3));
}

void yy(int a4[]) {
	printf("sizeof(a4) = %lu\n", sizeof(a4));
}

int main() {
	char a1[] = "abc";
	int a2[3];
	
	printf("sizeof(a1) = %lu\n", sizeof(a1));
	printf("sizeof(a2) = %lu\n", sizeof(a2));

	xx(a1);
	yy(a2);
	return 0;
}
