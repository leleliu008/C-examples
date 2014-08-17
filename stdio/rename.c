#include<errno.h>
#include<stdio.h>

int main() {
	int result = rename("output.dat", "output.data");
	if(0 == result) {
		printf("rename success!\n");
	} else if(-1 == result) {
		perror("rename fail");
		
		if(EACCES == errno) {
			printf("权限不够\n");
		} else if(EBUSY == errno) {
			printf("BUSY\n");
		} else {
			printf("位置错误!\n");
		}
	}
	return 0;
}
