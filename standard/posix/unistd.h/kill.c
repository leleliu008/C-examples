#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<stdio.h>

void signalHandler(int signum) {
	if(SIGINT == signum) {
		printf("收到了杀死进程%d的信号\n", getpid());
	}
}

int main() {
	/* 注册消息处理 */
	signal(SIGINT, signalHandler);
	
	/* 获得主进程的pid */
	pid_t main_pid = getpid();
	
	/* fork一个新进程 */
	pid_t new_pid = fork();

	if(new_pid < 0) {
		perror("fork error!\n");
	} else if(0 == new_pid) {
		/* 杀死主进程 */
		kill(main_pid, SIGINT);
		printf("process %d kill process %d\n", getpid(), main_pid);
	} else {
		sleep(10);
	}

	return 0;
}
