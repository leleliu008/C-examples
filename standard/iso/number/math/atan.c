#include<stdio.h>
#include<float.h>
#include<math.h>

int main() {
	printf("atan(DBL_MAX) = %.16f\n", atan(DBL_MAX));
	printf("atan(-DBL_MAX) = %.16f\n", atan(-DBL_MAX));
	printf("atan(DBL_MIN) = %.16f\n", atan(DBL_MIN));
	printf("atan(-DBL_MIN) = %.16f\n", atan(-DBL_MIN));
	return 0;
}
