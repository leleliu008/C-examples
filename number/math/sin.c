#include<stdio.h>
#include<math.h>

int main() {
	printf("sin(-M_PI) = %f\n", sin(-M_PI));
	printf("sin(M_PI)  = %f\n", sin(M_PI));
	printf("sin(-M_PI_2) = %f\n", sin(-M_PI_2));
	printf("sin(M_PI_2)  = %f\n", sin(M_PI_2));
	printf("sin(-M_PI_4) = %f\n", sin(-M_PI_4));
	printf("sin(M_PI_4)  = %f\n", sin(M_PI_4));
	printf("sin(-M_PI / 6.0) = %f\n", sin(-M_PI / 6.0));
	printf("sin(M_PI / 6.0)  = %f\n", sin(M_PI / 6.0));
	return 0;
}
