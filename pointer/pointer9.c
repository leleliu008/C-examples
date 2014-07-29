/* 指针型函数示例 */

typedef enum {
	MON,
	TUE,
	WED,
	THU,
	FRI,
	SAT,
	SUN
} WeekDay;

char *weekday[] = { "Monday",
					"Tuesday",
					"Wednesday",
					"Thursday",
					"Friday",
					"Saturday",
					"Sunday"
				  };

char* getName(WeekDay whichDay) {
	return weekday[whichDay];
}

int main() {
	char *a = getName(MON);
	char *b = getName(TUE);
	char *c = getName(WED);
	char *d = getName(THU);
	char *e = getName(FRI);
	char *f = getName(SAT);
	char *g = getName(SUN);
	return 0;
}
