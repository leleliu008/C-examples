#include<stdio.h>

int main() {
	FILE *fp = fopen("output.dat", "w");
	if(NULL != fp) {
		char *str = "Hello World!";
		fwrite(str, 1, 12, fp);
		fclose(fp);
	}
	return 0;
}
