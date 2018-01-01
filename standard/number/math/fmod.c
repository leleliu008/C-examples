#include<stdio.h>
#include<math.h>


int main() {
	printf("fmod(5.0, 3.0) = %.16f\n", fmod(5.0, 3.0));
	printf("fmod(5.2, 3.0) = %.16f\n", fmod(5.2, 3.0));
	printf("fmod(-5.2, 3.0) = %.16f\n", fmod(-5.2, 3.0));
	printf("fmod(5.2, -3.0) = %.16f\n", fmod(5.2, -3.0));
	printf("fmod(5.2, int(5.2)) = %.16f\n", fmod(5.2, (int)5.2));
	return 0;
}
