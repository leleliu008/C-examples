#include<stdio.h>
#include<float.h>
#include<math.h>

int main() {
	printf("floor(3.5) = %.16f\n", floor(3.5));
	printf("floor(-3.5) = %.16f\n", floor(-3.5));
	printf("floor(DBL_MIN) = %.16f\n", floor(DBL_MIN));
	printf("floor(-DBL_MIN) = %.16f\n", floor(-DBL_MIN));
	return 0;
}
