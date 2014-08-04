/* 两变量交换内容的通用方法 */

int main() {
	char a = 'A';
	char b = 'a';
	char tmp;

	tmp = a;
	a = b;
	b = tmp;

	return 0;
}
