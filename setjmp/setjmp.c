#include<setjmp.h>

static jmp_buf env;

void foo() {
	puts("in foo");
	longjmp(env, 1);
}

int main() {
	if(!setjmp(env)) {
		puts("you can see this");
		foo();
		puts("never see this");
	} else {
		puts("catch an exception");
	}

	puts("finally");

	return 0;
}
