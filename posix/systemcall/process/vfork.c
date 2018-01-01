#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main() {
	int data = 0;
	pid_t pid = vfork();

	if(pid < 0) {
		perror("vfork error!");
	} else if (pid == 0) {
		printf("i'm child process and my pid is %d\n", getpid());
		data = 20;
		execlp("ls", "ls", "-l", NULL);
	} else {
		printf("i'm parent process and my pid is %d\n", getpid());
		printf("i'm parent process and new process pid is %d\n", pid);
		printf("parent process data = %d\n", data);
	}

	return 0;
}
