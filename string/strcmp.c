#include<string.h>

int main() {
	char *str1 = "abc";
	char *str2 = "abd";
	char *str3 = "abcd";
	int rc1 = strcmp(str1, str2);
	int rc2 = strcmp(str1, str3);
	return 0;
}
