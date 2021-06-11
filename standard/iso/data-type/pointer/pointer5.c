/* 两个指针相减，两个指针相加没有意思 */

int main() {
	int a[6] = {1, 2, 3, 4, 5, 6};

	int *p1 = a;
	int *p2 = &a[3];
	int *p3 = &a[5];
	
	_Bool isXX = p2 > p1;
	_Bool isYY = p2 > p3;

	return 0;
}
