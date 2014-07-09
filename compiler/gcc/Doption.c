/* 测试gcc的-D选项*/
 
#include<stdio.h>

int main() {
#ifdef DEBUG
	printf("debug\n");
#else
	printf("release\n");
#endif
	return 0;
}
