/* strlen函数测试 */

#include<string.h>

int main() {
	char str[] = "Hello\0world";
	size_t length = strlen(str);
	str[5] = ' ';
	length = strlen(str);
	return 0;
}
