/* 局部静态变量 */

#include<stdio.h>

void func() {
	static int count;
	count++;
	printf("%d\n", count);
}

int main() {
	int i;
	for(i = 0; i < 10; i++) {
		func();
	}
	return 0;
}
