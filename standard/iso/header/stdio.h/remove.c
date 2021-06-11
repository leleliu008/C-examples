#include<stdio.h>

int main() {
	int result = remove("output.dat");
	if(0 == result) {
		printf("remore success!\n");
	} else if(-1 == result) {
		perror("remove fail");
	}
	return 0;
}
