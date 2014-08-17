#include<stdio.h>

int main() {
	FILE *fp = fopen("fgets.c", "r");
	if(NULL != fp) {
		char buff[10];
		buff[9] = '\0';
		
		char *p = fgets(buff, 9, fp);
		if(NULL != p) {
			printf("%s\n", p);
		}
		
		fclose(fp);
	}
	
	return 0;
}
