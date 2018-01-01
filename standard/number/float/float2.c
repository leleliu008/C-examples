/* 测试浮点数的精度 */

#include<stdio.h>

int main() {
	float a = 1234567.89;
	double b = 1234567.89123456789;
	printf("a = %f\n", a);
	printf("b = %.11f\n", b);
	return 0;
}
