#include<stdio.h>
#include<float.h>
#include<errno.h>
#include<math.h>

int main() {
	printf("log(DBL_MAX) = %.16f\n", log(DBL_MAX));
	printf("log(M_E) = %.16f\n", log(M_E));
	printf("log(DBL_MIN) = %.16f\n", log(DBL_MIN));

	double x = log(0.0);
	extern int errno;
	if(EDOM == errno) {
		printf("log(0.0)超过了定义域\n");
	} else if(ERANGE == errno) {
		printf("log(0.0)的值超过了范围\n");
	}
	
	return 0;
}
