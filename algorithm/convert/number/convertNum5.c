/* 交换两个数，不使用第三个参数*/

int main() {
	int a = 3;
	int b = 4;

	b = a + 0 * (a = b);

	return 0;
}
