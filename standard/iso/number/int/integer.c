#include<limits.h>
#include<stdio.h>

int main() {
	//有符号的短整型
	printf("sizeof(signed short int) = %d\n", sizeof(signed short int));
	printf("SHRT_MAX = %d\n", SHRT_MAX);
	printf("SHRT_MIN = %d\n", SHRT_MIN);
	printf("\n");

	//无符号的短整型
	printf("sizeof(unsigned short int) = %d\n", sizeof(unsigned short int));
	printf("USHRT_MAX = %u\n", USHRT_MAX);
	printf("\n");

	//有符号的整型
	printf("sizeof(singed int) = %d\n", sizeof(signed int));
	printf("INT_MAX = %d\n", INT_MAX);	
	printf("INT_MIN = %d\n", INT_MIN);
	printf("\n");

	//无符号的整型
	printf("sizeof(unsigned int) = %d\n", sizeof(unsigned int));
	printf("UINT_MAX = %u\n", UINT_MAX);
	printf("\n");
	
	//有符号的长整型
	printf("sizeof(signed long int) = %d\n", sizeof(signed long int));
	printf("LONG_MAX = %ld\n", LONG_MAX);
	printf("LONG_MIN = %ld\n", LONG_MIN);
	printf("\n");

	//无符号的长整型
	printf("sizeof(unsigned long int) = %d\n", sizeof(unsigned long int));
	printf("ULONG_MAX = %lu\n", ULONG_MAX);
	printf("\n");

	//有符号的增长整型
	printf("sizeof(signed long long int) = %d\n", sizeof(signed long long int));
	printf("LLONG_MAX = %lld\n", LLONG_MAX);
	printf("LLONG_MIN = %lld\n", LLONG_MIN);
	printf("\n");

	//无符号的增长整型
	printf("sizeof(unsigned long long int) = %d\n", sizeof(unsigned long long int));
	printf("ULLONG_MAX = %llu\n", ULLONG_MAX);
	printf("\n");

	/*---------------------------------------------------*/
	
	/*---------------------------------------------------*/
	return 0;
}
