#include<unistd.h>
#include<stdio.h>

int main() {
	pid_t pid = getpid();
	printf("my pid is %d\n", pid);
	return 0;
}
