/* 有名枚举的定义 */

enum WeekDay {
	MON, /* 星期一 */
	TUE, /* 星期二 */
	WED, /* 星期三 */
	THU, /* 星期四 */
	FRI, /* 星期五 */
	SAT, /* 星期六 */
	SUN  /* 星期日 */
} today, tomorrow;

#include<stdio.h>

int main() {
	today = SUN;
	tomorrow = MON;
	printf("today = %d\n", today);
	printf("tomorrow = %d\n", tomorrow);
	
	return 0;
}
