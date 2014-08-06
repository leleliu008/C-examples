#include<stdio.h>
#include<float.h>
#include<math.h>

int main() {
	printf("atan(0.75) = %.16f\n", atan(0.75));
	printf("atan2(3.0, 4.0) = %.16f\n", atan2(3.0, 4.0));
	printf("tan2(DBL_MAX, DBL_MIN) = %.16f\n", atan2(DBL_MAX, DBL_MIN));
	return 0;
}
