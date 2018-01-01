#include<stdio.h>

int main() {
	FILE *fp = freopen("fgets.c", "r", stdin);
	if(NULL != fp) {
		char buff[10];
		buff[9] = '\0';
		
		char *p = gets(buff);
		if(NULL != p) {
			printf("%s\n", p);
		}
		
		fclose(fp);
	}
	
	return 0;
}
