/* 两个数交换 */
void swap(int *a, int *b) {
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int main() {
	int a = 10;
	int b = 20;
	swap(&a, &b);

	/*此处打断点查看 */

	return 0;
}
