#include<string.h>

int main() {
	char des[10] = "abc";
	char *src = "def\0ghkl";
	strcat(des, src);
	return 0;
}
