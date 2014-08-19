#include<stdio.h>
#include<time.h>

int main() {
	time_t tt = time(NULL);
	struct tm *gmt = gmtime(&tt);
	printf("现在是GMT时间：%d年%d月%d日 %-2d:%-2d:%-2d\n", \
			1900 + gmt->tm_year, 1 + gmt->tm_mon, gmt->tm_mday, \
			gmt->tm_hour, gmt->tm_min, gmt->tm_sec);
	
	struct tm *loct = localtime(&tt);
	printf("现在是北京时间：%d年%d月%d日 %-2d:%-2d:%-2d\n", \
			1900 + loct->tm_year, 1 + loct->tm_mon, loct->tm_mday, \
			loct->tm_hour, loct->tm_min, loct->tm_sec);
	
	return 0;
}
