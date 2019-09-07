#include<stdio.h>
#include<errno.h>
#include<math.h>

int main() {
	printf("sqrt(5) = %f\n", sqrt(5));
	
	double x = sqrt(-5);
	extern int errno;
	if(EDOM == errno) {
		printf("sqrt(-5)超过了定义域\n");
	} else if(ERANGE == errno) {
		printf("sqrt(-5)的值超过了定义域\n");
	}
	
	return 0;
}
