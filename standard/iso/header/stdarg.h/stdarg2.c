#include<stdarg.h>
#include<stdio.h>

void func(int arg0, ...) {
	va_list vars;
	
	va_start(vars, arg0);

	printf("%d  ", arg0);

	int var;
	while(1) {
		var = va_arg(vars, int);
		if(-1 != var) {
			printf("%d  ", var);
		} else {
			break;
		}
	}
	
	va_end(vars);

	putchar('\n');
}

int main() {
	func(6, 10, -3, 2, 6, 9, -1);
	func(3, 2, 3, -1);
	func(1, -1);
	
	return 0;
}
