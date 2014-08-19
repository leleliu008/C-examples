#include<stdlib.h>
#include<stdio.h>

static void onexit() {
	printf("onexit()\n");
}

int main() {
	if(0 != atexit(onexit)) {
		printf("atexit fail\n");
	}
	return 0;
}
