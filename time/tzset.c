#include<stdio.h>
#include<time.h>

int main() {
	setenv("TZ", "GMT-9", 1);
	tzset();
	time_t t = time(NULL);
	printf("%s\n", asctime(localtime(&t)));

	return 0;
}
