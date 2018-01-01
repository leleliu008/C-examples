#include<stdio.h>

int main() {
	FILE *tmp = tmpfile();
	if(NULL != tmp) {
		fprintf(tmp, "Hello");
		fclose(tmp);
	}
	return 0;
}
