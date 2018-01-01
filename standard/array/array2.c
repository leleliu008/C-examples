/* 一维数组的定义*/

#define LENGTH 5

int main() {
	/* 全部元素初始化 */
	int a[5] = {1, 3, 5, 7, 9};
	/* 部分元素初始化 */
	int a2[5] = {1,2,3};

	float b[LENGTH] = {2.0f, 3.1f, 4.2f, 5.3f, 8.9f};
	char c[5 * 2] = {'A', 'B', 'C', 'D', 'E', 'a', 'b', 'c', 'd', 'e'};
	char e[11] = "ABCDEabcde";

	/* C99支持的形式，C89、C90不支持 */ 
	int n = 5;
	double d[n]; 
	d[0] = 2.0;
	d[1] = 3.0;
	d[2] = 4.0;
	d[3] = 5.0;
	d[4] = 6.0;

	return 0;
}
