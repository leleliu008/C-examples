#include<stdlib.h>
#include<stdio.h>

int main(int argc, char *argv[]) {
	if(atoi(argv[1]) > 0) {
		printf("goto label\n");
		goto label;
	}

	label: perror("occur error!");
	
	return 0;
}
