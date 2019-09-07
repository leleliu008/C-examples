#include<time.h>
#include<stdio.h>

int main() {
	time_t tt = time(NULL);
	struct tm *t = localtime(&tt);
	char *ft = asctime(t);
	printf("现在是：%s", ft);
	return 0;
}
