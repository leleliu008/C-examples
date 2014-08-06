#include<stdio.h>
#include<float.h>
#include<math.h>

int main() {
	printf("tanh(3.0) = %.16f\n", tanh(3.0));
	printf("tanh(-3.0) = %.16f\n", tanh(-3.0));
	printf("tanh(DBL_MAX) = %.16f\n", tanh(DBL_MAX));
	printf("tanh(-DBL_MAX) = %.16f\n", tanh(-DBL_MAX));
	printf("tanh(DBL_MIN) = %.16f\n", tanh(DBL_MIN));
	return 0;
}
