#include<stdio.h>
#include<ctype.h>

int main() {
	int count = 0;
	int i = 0;

	for(i = 0; i <= 255; i++) {
		if(isspace(i)) {
			printf("\'%c\' = %-5d", i, i);
			
			if(++count % 7 == 0) {
				printf("\n");
			}
		}
	}

	printf("\n");

	return 0;
}

