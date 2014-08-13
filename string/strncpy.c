#include<string.h>

int main() {
	char dest[10] = "abc";
	char *src = "def\0ghklmnop";
	strcpy(dest, src);
	strncpy(dest, src, 10);
	return 0;
}
