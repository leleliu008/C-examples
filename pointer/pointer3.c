/* 两个指针相减，两个指针相加没有意思 */

int main() {
	int a[6] = {1, 2, 3, 4, 5, 6};
	int *p1 = a;
	int *p2 = &a[5];
	int delta = p2 - p1;
	return 0;
}
