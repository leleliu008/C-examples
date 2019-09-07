/* 同一个字符的不同表示显示 */

#include<stdio.h>

int main() {
	char a = 'A';
	char b = 65;
	char c = 0101;
	char d = 0x41;
	char e = '\101';
	char f = '\x41';

	printf("a = %c\n", a);
	printf("b = %c\n", b);
	printf("c = %c\n", c);
	printf("d = %c\n", d);
	printf("e = %c\n", e);
	printf("f = %c\n", f);

	return 0;
}
