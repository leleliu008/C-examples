#include<stdio.h>

#define DEBUG 0

int main() {
    #if DEBUG
	printf("debugging...");
    #endif
	printf("running...");
    return 0;
}
