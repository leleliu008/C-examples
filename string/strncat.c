#include<string.h>

int main() {
	char des[10] = "abc";
	char *src = "def\0ghkl";
	strncat(des, src, 8);
	return 0;
}
