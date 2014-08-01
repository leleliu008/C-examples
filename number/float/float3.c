/* 浮点数不能比较相等 */

#include<stdio.h>
#include<float.h>
#include<math.h>

int main() {
	double a = 0.5;
	double b = sin(M_PI / 6.0);
	printf("b = %f\n", b);
	if(fabs(a - b) < DBL_EPSILON) {
		printf("a == b\n");
	} else {
		printf("a != b\n");
	}
	return 0;
}
