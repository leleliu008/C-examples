#include<stdio.h>

int main() {
	FILE *fp = fopen("ftell.c", "r");
	if(fp) {
		if(0 == fseek(fp, 0L, SEEK_END)) {
			long length = ftell(fp);
			printf("ftell.c is %ld Byte\n", length);
		}

		fclose(fp);
	}
	return 0;
}
