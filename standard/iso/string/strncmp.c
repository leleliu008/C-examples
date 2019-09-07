#include<string.h>

int main() {
	char *str1 = "abc";
	char *str2 = "abd";
	char *str3 = "abcd";
	int rc1 = strncmp(str1, str2, 2);
	int rc2 = strncmp(str1, str3, 2);
	int rc3 = strncmp(str1, str2, 3);
	int rc4 = strncmp(str1, str3, 3);
	int rc5 = strncmp(str1, str2, 4);
	int rc6 = strncmp(str1, str3, 4);
	return 0;
}
