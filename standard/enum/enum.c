/* 匿名枚举的定义 */

enum {
	MON, /* 星期一 */
	TUE, /* 星期二 */
	WED, /* 星期三 */
	THU, /* 星期四 */
	FRI, /* 星期五 */
	SAT, /* 星期六 */
	SUN  /* 星期日 */
};

#include<stdio.h>

int main() {
	printf("MON = %d\n", MON);
	printf("TUE = %d\n", TUE);
	printf("WED = %d\n", WED);
	printf("THU = %d\n", THU);
	printf("FRI = %d\n", FRI);
	printf("SAT = %d\n", SAT);
	printf("SUN = %d\n", SUN);

	return 0;
}
