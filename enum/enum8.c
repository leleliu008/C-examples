/* 有名枚举的定义 */

typedef enum {
	MON, /* 星期一 */
	TUE, /* 星期二 */
	WED, /* 星期三 */
	THU, /* 星期四 */
	FRI, /* 星期五 */
	SAT, /* 星期六 */
	SUN  /* 星期日 */
} WeekDay;

#include<stdio.h>

int main() {
	WeekDay today = SUN;
	today = 1;
	today = 'A';
	today += 2;
	int x = today;
	printf("x = %d\n", x);
	printf("today = %d\n", today);
	return 0;
}
