#include<stdio.h>

int main() {
	int a[3][4] = {{1, 2, 3, 4}, {5, 6, 7 ,8}, {9, 10 , 11, 12}};
	
	int (*p)[4];
	p = a;

	int i,j;
	
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 4; j++) {
			printf("%-2d ", *(*(p + i) + j));
		}
		printf("\n");
	}

	return 0;
}
