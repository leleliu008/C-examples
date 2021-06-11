/* puts函数的测试 */

#include<stdio.h>

int main() {
	char str1[] = "I Love you!";
	char *p = "C Program";

	if(EOF == puts(str1)) {
		perror("puts发生了错误");
	}
	
	if(puts(p)) {
		printf("success\n");
	}

	return 0;
}
