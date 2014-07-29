/* C语言中数组越界并不会报错，但是越界可能会出现一些致命错误 */

#include<stdio.h>

#define LENGTH 5

int main() {
	int a[LENGTH] = {1, 2, 3, 4, 5};
	int i;
	for(i = 0; i <= LENGTH; i++) {
		printf("%d  ", a[i]);
	}
	printf("\n");
	return 0;
}
