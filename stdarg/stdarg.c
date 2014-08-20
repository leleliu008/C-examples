#include<stdarg.h>
#include<stdio.h>

void func(int count, ...) {
	va_list vars;
	
	va_start(vars, count);

	int i;
	for(i = 0; i < count; i++) {
		int var = va_arg(vars, int);
		printf("%d  ", var);
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
