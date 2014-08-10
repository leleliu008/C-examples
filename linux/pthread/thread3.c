#include<stdio.h>
#include<pthread.h>

/* 线程要执行的函数 */
void *run(void *args) {
	printf("running start\n");
	int i;
	for(i = 0; i < 100; i++) {
		printf("running...\n");
	}
	printf("running end\n");
	return NULL;
}

int main() {
	pthread_t threadId;
	int rc = pthread_create(&threadId, NULL, run, NULL);
	if(0 != rc) {
		printf("create thread fail!\n");
		return -1;
	}

	if(threadId, pthread_self()) {
		printf("是同一个线程!\n");
	}

	printf("create thread success\n");

	pthread_exit("main thread exit\n");

	return 0;
}
