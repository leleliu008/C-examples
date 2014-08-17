#include<stdio.h>

int main() {
	if(NULL == freopen("freopen.c", "r", stdin)) {
		perror("将freopen.c重定向到stdin失败");
	}

	if(NULL == freopen("output.data", "w", stdout)) {
		perror("将stdout重定向到output.data失败");
	}
	printf("在output.data文件中");

	if(NULL == freopen("/dev/tty", "w", stdout)) {
		perror("将output.data重定向到控制台失败");
	}
	printf("在控制台显示\n");

	return 0;
}
