#include<unistd.h>
#include<stdio.h>

int main() {
	pid_t ppid = getppid();
	pid_t pid = getpid();
	return 0;
}
