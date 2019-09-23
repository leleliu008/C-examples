/* 两变量交换内容的通用方法
 * 使用gdb等调试器调试，观察变量的地址宽度
 */

int main() {
	char a = 'A';
	char b = 'a';
	char tmp;

	tmp = a;
	a = b;
	b = tmp;

	return 0;
}
