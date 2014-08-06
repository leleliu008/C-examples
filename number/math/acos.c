#include<stdio.h>
#include<errno.h>
#include<math.h>

int main() {
	printf("acos(1.0) = %f\n", acos(1.0));
	printf("acos(-1.0) = %f\n", acos(-1.0));

	double acos_5 = acos(5);
	extern int errno;
	if(EDOM == errno) {
		printf("cos(5)超过了定义域\n");
	} else if (ERANGE == errno) {
		printf("cos(5)超过了值域\n");
	}

	return 0;
}
