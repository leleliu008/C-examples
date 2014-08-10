#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

int main() {
	int i;
	for(i = 0; i < 3; i++) {
		pid_t pid = fork();
		if(pid < 0) {
			printf("创建第%d个进程失败!\n", i);
		} else if(0 == pid) {
			printf("创建第%d个进程成功，pid = %d\n", i, getpid());
		}
	}

	pid_t child_pid;
	for(i = 0; (child_pid = wait(NULL)) > 0; i++) {
		printf("捕获了第%d个子进程，pid = %d\n", i, child_pid);
	}

	return 0;
}
