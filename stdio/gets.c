/* gets函数的测试 */

#include<stdio.h>

int main() {
	char buff[10];
	
	printf("Please input some message:");
	gets(buff);
	puts(buff);
	return 0;
}
