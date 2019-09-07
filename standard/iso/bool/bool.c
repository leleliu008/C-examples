#include<stdio.h>
#include<stdbool.h>

int main() {
	_Bool isXXX = false;
	bool isYYY = true;
	bool isZZZ = 0;
	bool isVVV = 1;
	bool isTTT = -12;
	bool isNNN = 'A';
	
	printf("sizeof(bool) = %lu\n", sizeof(bool));
	printf("isXXX = %d\n", isXXX);
	printf("isYYY = %d\n", isYYY);
	printf("isZZZ = %d\n", isZZZ);
	printf("isVVV = %d\n", isVVV);
	printf("isTTT = %d\n", isTTT);
	printf("isNNN = %d\n", isNNN);

	return 0;
}
