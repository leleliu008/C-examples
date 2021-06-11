#include<stdio.h>

int main() {
	FILE *fp = freopen("fgets.c", "r", stdin);
	if(NULL != fp) {
		fp->_flags;

        char buff[10] = {0};
		
		char *p = gets(buff);
		if(NULL != p) {
			printf("%s\n", p);
		}
		
		fclose(fp);
	}
	
	return 0;
}
