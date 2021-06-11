#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

/* 回调函数 */
void signalHandler(int signum) {
	if(SIGINT == signum) {
		printf("您点击了键盘Ctrl+C\n");
		exit(0);
	}
}

int main() {
	/* 注册回调函数 */
	signal(SIGINT, &signalHandler);

	/* 开始消息循环 */
	while(1) {
		sleep(1);
	}
	
	return 0;
}
