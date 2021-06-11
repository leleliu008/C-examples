#include<stdio.h>

int main() {
	FILE *fp = fopen("fgetpos.c", "r");
	if(NULL != fp) {
		fpos_t pos;
		fgetpos(fp, &pos);
	}
	return 0;
}
