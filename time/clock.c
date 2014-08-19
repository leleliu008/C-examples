#include<stdio.h>
#include<time.h>

int main() {
	clock_t ct = clock();

	printf("启动时间为：%ld毫秒\n", ct);
	printf("启动时间为：%ld秒\n", ct / CLOCKS_PER_SEC);

	return 0;
}
