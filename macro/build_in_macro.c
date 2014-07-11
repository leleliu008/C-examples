#include<stdio.h>
#include<stdlib.h>

#define DATE_TIME __DATE__" "__TIME__

void func() {
	printf("release date_time=%s, file=%s, line=%d, fuction=%s\n",\
			DATE_TIME, __FILE__, __LINE__, __func__);
}

int main() {
	func();
	printf("release date_time=%s, file=%s, line=%d, fuction=%s\n",\
			DATE_TIME, __FILE__, __LINE__, __func__);
	return 0;
}
