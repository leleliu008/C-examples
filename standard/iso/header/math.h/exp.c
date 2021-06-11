#include<stdio.h>
#include<float.h>
#include<errno.h>
#include<math.h>

int main() {
	double x = exp(DBL_MAX);
	extern int errno;
	if(EDOM == errno) {
		printf("exp(DBL_MAX)超过了定义域\n");
	} else if(ERANGE == errno) {
		printf("exp(DBL_MAX)的值超过了范围\n");
	}

	printf("exp(-DBL_MAX) = %.16f\n", exp(-DBL_MAX));
	printf("exp(DBL_MIN) = %.16f\n", exp(DBL_MIN));
	printf("exp(-DBL_MIN) = %.16f\n", exp(-DBL_MIN));
	return 0;
}
