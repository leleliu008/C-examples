#include<stdio.h>

#define ONE 1
#define TWO 2
#define THREE 3

int main() {
	#ifdef ONE
		printf("%d\n", ONE);
	#elif defined TWO
		printf("%d\n", TWO);
	#else
		printf("%d\n", THREE);
	#endif

	return 0;
}
