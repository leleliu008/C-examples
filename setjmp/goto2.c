#include<stdio.h>

int main() {
	int i = 1;
	
	label: printf("%-4d", i);
	
	if(i < 10) {
		i++;
		goto label;
	}
	
	printf("\n");

	return 0;
}
