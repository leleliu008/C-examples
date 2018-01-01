/* strlen函数测试 */

#include<string.h>
#include<stdio.h>

int main() {
	char str[] = "Hello\0world";
	size_t length = strlen(str);
	printf("%s, %lu\n", str, length);
	
	str[5] = '\n';
	length = strlen(str);
	printf("%s, %lu\n", str, length);
	
	return 0;
}
