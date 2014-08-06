#include<stdio.h>
#include<float.h>
#include<errno.h>
#include<math.h>

int main() {
	printf("sinh(10) = %.16f\n", sinh(10));
	printf("sinh(-10) = %.16f\n", sinh(-10));

    double x = sinh(DBL_MAX);
	extern errno;
	if(EDOM == errno) {
		printf("sinh(DBL_MAX)超过了定义域\n");
	} else if(ERANGE == errno) {
		printf("sinh(DBL_MAX)的值超过了范围\n");
	}
	return 0;
}
