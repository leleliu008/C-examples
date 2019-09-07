#include<stdio.h>

int main() {
	printf("sizeof(int) = %lu\n", sizeof(int));
	printf("sizeof(2 + 3.0f) = %lu\n", sizeof(2 + 3.0f));
	
	int i;
	printf("sizeof(i) = %lu\n", sizeof(i));
	printf("sizeof i = %lu\n", sizeof i);
	
	printf("sizeof(2) = %lu\n", sizeof(2));
	printf("sizeof 2 = %lu\n", sizeof 2);
	
	printf("sizeof(fabs(3.0f) = %lu\n)", sizeof(fabs(3.0f)));

	//编译时刻确定，所以是常量
	char ch1[sizeof(int) * 10];
	
	int n = 10;
	char ch[n];
	printf("sizeof(ch) = %lu\n", sizeof(ch));


	return 0;
}
