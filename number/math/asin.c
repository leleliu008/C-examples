#include<stdio.h>
#include<errno.h>
#include<math.h>

int main() {
	printf("asin(1.0) = %f\n", asin(1.0));
	printf("asin(-1.0) = %f\n", asin(-1.0));

	double asin_5 = asin(5);
	extern int errno;
	if(EDOM == errno) {
		printf("sin(5)超过了定义域\n");
	} else if (ERANGE == errno) {
		printf("sin(5)超过了值域\n");
	}

	return 0;
}
