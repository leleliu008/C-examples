#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main() {
	pid_t pid = fork();

	if(pid < 0) {
		perror("fork error!\n");
	} else if(0 == pid) {
		/* 退出子进程 */
		exit(0);
	} else {
		sleep(60);
		wait(NULL);
	}

	return 0;
}
