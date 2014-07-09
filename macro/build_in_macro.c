#include<stdio.h>
#include<stdlib.h>

void func() {
	printf("release date=%s, time=%s, fileName=%s, line=%d, fuction=%s\n",\
			__DATE__, __TIME__, __FILE__, __LINE__, __func__);
}

int main() {
	func();
	printf("release date=%s, time=%s, fileName=%s, line=%d, fuction=%s\n",\
			__DATE__, __TIME__, __FILE__, __LINE__, __func__);
	return 0;
}
