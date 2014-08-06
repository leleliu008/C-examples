#include<stdio.h>
#include<float.h>
#include<math.h>

int main() {
	printf("ceil(3.5) = %.16f\n", ceil(3.5));
	printf("ceil(-3.5) = %.16f\n", ceil(-3.5));
	printf("ceil(DBL_MIN) = %.16f\n", ceil(DBL_MIN));
	printf("ceil(-DBL_MIN) = %.16f\n", ceil(-DBL_MIN));
	return 0;
}
