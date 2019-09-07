#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main() {
	printf("RAND_MAX = %d\n", RAND_MAX);

	//产生随机种子
	srand(time(NULL));

	int i, j;
	for(i = 0; i < 10; i++) {
		j = 10.0 * rand() / RAND_MAX;
		printf("%-4d", j);
	}

	printf("\n");

	return 0;
}
