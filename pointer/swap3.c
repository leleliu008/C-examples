/* 两个数交换 */
void swap(int *a, int *b) {
	int* tmp;
	*tmp = *a; /* tmp没有初始化就使用，出现了非法地址*/
	*a = *b;
	*b = *tmp;
}

int main() {
	int a = 10;
	int b = 20;
	swap(&a, &b);

	/*此处打断点查看 */

	return 0;
}
