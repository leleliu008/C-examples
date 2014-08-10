#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main() {
	pid_t pid = fork();

	if(pid < 0) {
		perror("fork error!\n");
	} else if(0 == pid) {
		printf("this is child process wtih pid of %d\n", getpid());
		sleep(10);
	} else {
		pid_t child_pid = wait(NULL);
		printf("main process catched a child process with pid of %d\n", child_pid);
	}

	return 0;
}
