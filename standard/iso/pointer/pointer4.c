/* 任意的两个指针相减，没有意义 */

int main() {
	int a = 5;
	char b = 'A';
	int c = 6;

	int *pa = &a;
	char *pb = &b;
	int *pc = &c;

	int delta = pc - pa;
	return 0;
}
