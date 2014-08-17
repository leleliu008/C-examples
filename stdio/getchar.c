#include<stdio.h>

int main() {
	FILE *fp = freopen("fgetc.c", "r", stdin);
	if(NULL != fp) {
		int ch = getchar();
		if(EOF != ch) {
			printf("%c\n", ch);
		}
		
		fclose(fp);
	}
	return 0;
}
