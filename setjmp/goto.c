#include<stdio.h>

int main() {
	int i = 1;
	if(i > 0) {
		goto label;
	}

	label: perror("occur error!");
	
	return 0;
}
