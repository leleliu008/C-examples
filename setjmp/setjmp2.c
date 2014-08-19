#include<setjmp.h>

static jmp_buf env;

#define try if(!setjmp(env))
#define catch else
#define throwException longjmp(env, 1)

void foo() {
	puts("in foo");
	throwException;
}

int main() {
	try {
		puts("you can see this");
		foo();
		puts("never see this");
	} catch {
		puts("catch an exception");
	}

	puts("finally");

	return 0;
}
