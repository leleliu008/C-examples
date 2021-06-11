#include<stdio.h>
#include<time.h>

int main() {
	time_t startt = time(NULL);
	sleep(2);
	time_t endt = time(NULL);
	double daltet = difftime(endt, startt);
	printf("耗时%f秒\n", daltet);
	return 0;
}
