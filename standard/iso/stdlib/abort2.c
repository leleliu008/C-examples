#include<signal.h>
#include<stdlib.h>
#include<stdio.h>

void signalHandler(int signum) {
	printf("catch signal SIGABRT\n");
}

int main() {
	signal(SIGABRT, signalHandler);
	abort();
	return 0;
}
