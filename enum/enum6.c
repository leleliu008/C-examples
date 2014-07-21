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
	
	printf("sizeof(WeekDay) = %lu\n", sizeof(WeekDay));
	printf("sizeof(today) = %lu\n", sizeof(today));
	printf("sizeof(MON) = %lu\n", sizeof(MON));
	
	return 0;
}
