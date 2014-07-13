#include<stdio.h>

int main() {
	int fpid = fork();
	if(fpid < 0) {
		printf("fork error!");
	} else if (fpid == 0) {
		printf("im child process and my pid is %d\n", getpid());
	} else {
		printf("im parent process and my pid is %d\n", getpid());
	}

	//int i = 0;
	//for(; i < 1000000; i++) {
		//printf("%d\n", i);
	//}
}
