#include<stdio.h>
#include<stdlib.h>

int main(int argc, char * argv[]) {
	int i;
	for(i = 1; i < argc; i++) {
		printf("String convert to int:%d\n", atoi(argv[i]));
		printf("String convert to long int:%ld\n", atol(argv[i]));
		printf("String convert to long long int:%lld\n", atoll(argv[i]));
		printf("String convert to double:%f\n", atof(argv[i]));
		if(i < argc - 1) {
			printf("----------------------\n");
		}
	}
	return 0;
}

