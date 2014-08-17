/* fputs函数的测试 */

#include<stdio.h>

int main() {
	char str1[] = "I Love you!";
	char *p = "C Program";

	if(EOF == fputs(str1, stdout)) {
		perror("puts发生了错误");
	}
	
	if(fputs(p, stdout)) {
		printf("success\n");
	}

	return 0;
}
