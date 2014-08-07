#include<stdio.h>
#include<float.h>
#include<errno.h>
#include<math.h>

int main() {
	printf("cosh(10) = %.16f\n", cosh(10));
	printf("cosh(-10) = %.16f\n", cosh(-10));
	printf("cosh(DBL_MIN) = %.16f\n", cosh(DBL_MIN));

    double x = cosh(DBL_MAX);
	extern errno;
	if(EDOM == errno) {
		printf("cosh(DBL_MAX)超过了定义域\n");
	} else if(ERANGE == errno) {
		printf("cosh(DBL_MAX)的值超过了范围\n");
	}

	return 0;
}
