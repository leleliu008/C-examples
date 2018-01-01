/* 寄存器变量 */

#include<stdio.h>

int main() {
	register int i, sum;
	
	for(i = 0, sum = 0; i < 200; i++) {
		sum += i;
	}
	
	printf("sum = %d\n", sum);

	return 0;
}
