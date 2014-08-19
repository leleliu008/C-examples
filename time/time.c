#include<time.h>

int main() {
	time_t t1 = time(NULL);

	time_t t2;
	time(&t2);

	return 0;
}
