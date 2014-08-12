#include<unistd.h>
#include<stdio.h>

int main() {
	if(execl("/bin/echo", "", "executed by execl!", NULL) < 0) {
		perror("execl error!");
	}
	printf("execl success!\n");
	return 0;
}

