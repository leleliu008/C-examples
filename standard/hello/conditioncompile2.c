#include<stdio.h>

#define DEBUG

int main() {
	#ifdef DEBUG
		printf("yes\n");
	#else
		printf("no\n");
	#endif
	return 0;
}
