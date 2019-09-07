#include<stdio.h>
#include<unistd.h>

int main() {
	printf("output begin\n");
	printf("content in buffer");
	_exit(0);
	return 0;
}
