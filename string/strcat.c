#include<string.h>

int main() {
	char dest[10] = "abc";
	char *src = "def\0ghkl";
	strcat(dest, src);
	return 0;
}
