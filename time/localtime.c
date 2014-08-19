#include<time.h>
#include<stdio.h>

int main() {
	time_t tt = time(NULL);
	struct tm *loct = localtime(&tt);
	printf("现在是北京时间：%d年%d月%d日 %-2d:%-2d:%-2d\n", \
			1900 + loct->tm_year, 1 + loct->tm_mon, loct->tm_mday, \
			loct->tm_hour, loct->tm_min, loct->tm_sec);
	return 0;
}
