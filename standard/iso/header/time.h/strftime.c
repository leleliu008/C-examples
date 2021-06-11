#include<stdio.h>
#include<time.h>

int main() {
	time_t tt = time(NULL);
	struct tm *t = localtime(&tt);
	
	char buff[30];
	buff[29] = '\0';
	strftime(buff, 29, "%Y-%m-%d %H:%M:%S", t);
	printf("现在是北京时间：%s\n", buff);

	return 0;
}
