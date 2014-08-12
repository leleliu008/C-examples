#include<string.h>

int main() {
	char des[10] = "abc";
	char *source = "def\0ghklmnop";
	strcpy(des, source);
	strncpy(des, source, 10);
	return 0;
}
