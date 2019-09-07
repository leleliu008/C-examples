#include<unistd.h>
#include<stdio.h>

int main() {
	pid_t pid = fork();

	if(pid < 0) {
		perror("fork error!");
	} else if (pid == 0) {
		printf("i'm child process and my pid is %d\n", getpid());
	} else {
		printf("i'm parent process and my pid is %d\n", getpid());
		printf("i'm parent process and new process pid is %d\n", pid);
	}

	return 0;
}
