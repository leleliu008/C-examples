/* 函数指针测试 */

#include<stdio.h>

int max(int a, int b) {
	return a > b ? a : b;
}

int main() {
	int a = 3;
	int b = 4;
	
	/* 定义指向函数入口的指针变量 */
	int (*p)();
	p = max;

	int max = (*p)(a,b);

	return 0;
}
