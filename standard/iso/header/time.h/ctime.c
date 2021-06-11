#include<stdio.h>
#include<time.h>

int main() {
	time_t t = time(NULL);
	char *ft = ctime(&t);
	printf("现在是：%s\n", ft);
	return 0;
}
