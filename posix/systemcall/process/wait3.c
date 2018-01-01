#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

pid_t create_process() {
	static count;
	count++;

	pid_t pid = fork();
	if(pid < 0) {
		printf("创建第%d个进程失败!\n", count);
	} else if(0 == pid) {
		printf("创建第%d个进程成功，pid = %d\n", count, getpid());
	}

	return pid;
}

int main() {
	printf("\n");

	/* 创建3个子进程 */
	pid_t pid1 = create_process();
	if(pid1 > 0) {
		pid_t pid2 = create_process();
		if(pid2 > 0) {
			pid_t pid3 = create_process();
			if(pid3 > 0) {
				/* 睡眠1分钟，以便我们有充足的时间使用ps -au命令观察 */
				sleep(60);
				
				printf("\n");

				int i;
				pid_t child_pid;
				for(i = 1; (child_pid = wait(NULL)) > 0; i++) {
					printf("捕获了第%d个子进程，pid = %d\n", i, child_pid);
				}
			}
		}
	}

	return 0;
}
