#include<stdio.h>

int main() {
	FILE *fp = fopen("fgetc.c", "r");
	if(NULL != fp) {
		int ch = fgetc(fp);
		if(EOF != ch) {
			printf("%c\n", ch);
		}
		
		fclose(fp);
	}
	return 0;
}
