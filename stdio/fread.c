#include<stdio.h>

int main() {
	FILE *fp = fopen("fread.c", "r");
	if(NULL != fp) {
		char ch[1];
		while(0 != fread(ch, 1, 1, fp)) {
			printf("%c", ch[0]);
		}
		fclose(fp);
	}
	return 0;
}
