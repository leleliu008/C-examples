#include<stdio.h>
#include<stdlib.h>

int main(int argc, char * argv[]) {
	int i;
	for(i = 1; i < argc; i++) {
		printf("atoi\(\"%s\") = %d\n", argv[i], atoi(argv[i]));
		printf("atol\(\"%s\") = %ld\n", argv[i], atol(argv[i]));
		printf("atoll\(\"%s\") = %lld\n", argv[i], atoll(argv[i]));
		printf("atof\(\"%s\") = %f\n", argv[i], atof(argv[i]));
		if(i < argc - 1) {
			printf("----------------------\n");
		}
	}
	return 0;
}

