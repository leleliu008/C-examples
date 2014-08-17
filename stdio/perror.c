#include<errno.h>
#include<stdio.h>

int main() {
	errno = 0;
	perror("fail!");
	return 0;
}
