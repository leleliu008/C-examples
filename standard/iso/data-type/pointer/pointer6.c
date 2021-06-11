/* 两个任意类型的指针比较大小，没有意义 */

int main() {
	int a = 5;
	char b = 'A';
	int c = 6;

	int *pa = &a;
	char *pb = &b;
	int *pc = &c;

	_Bool ba = pb > pa;
	_Bool bb = pc > pb;
	_Bool bc = pc > pa;

	return 0;
}
