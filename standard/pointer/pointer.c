/* 指针定义和初始化 */

#include<stdlib.h>

int main() {
	int a = 100;
	float b = 20.0f;

	int *pa = &a;
	float *pb = &a; /* 这样会出现warnning，但不会出现error，这样很可能出现异常结果 */
	int *pc = 0x7fffffffd870;

	int d = *pa;

	/* 通过malloc函数进行内存分配 */
	int *pd = (int*) malloc(sizeof(int));
	if(NULL != pd) {
		*pd = 30;

		/* 此处打断点查看*/

		free(pd);
	}

	int e[5];
	int *pe = e;
	pe = &e[0];

	char *pf = "C Language";

	return 0;
}
