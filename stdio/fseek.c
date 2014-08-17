#include<stdio.h>

int main() {
	FILE *fp = fopen("output.dat", "w");
	if(NULL != fp) {
		long dalte = ftell(fp);
		char *p = "Hello";
		fwrite(p, 1, 5, fp);
		dalte = ftell(fp);
		
		fclose(fp);
	}
	return 0;
}
