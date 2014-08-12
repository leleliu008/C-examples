#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main() {
	pid_t pid = fork();

	if(pid < 0) {
		perror("fork error!");
	} else if(0 == pid) {
		printf("fork success! my pid is %d\n", getpid());
		exit(3);
	} else {
		int status;
		pid_t child_pid = wait(&status);
		if(WIFEXITED(status)) {
			printf("the child process %d exit normally!\n", child_pid);
			printf("the reutrn code is %d\n", WEXITSTATUS(status));
		} else {
			printf("the child process %d exit abnormally!\n", child_pid);
		}
	}

	return 0;
}
