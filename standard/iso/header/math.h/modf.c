#include<math.h>

int main() {
	double x = M_E;
	double a;
	modf(x, &a);
	return 0;
}
