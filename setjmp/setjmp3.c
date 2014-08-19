#include<setjmp.h>
#include<stdio.h>

static jmp_buf env;

void func1(int i) {
	puts("in func1");
	
	if(1 == i) {
		longjmp(env, 1);
	}
}

void func2(int i) {
	puts("in func2");

	if(2 == i) {
		longjmp(env, 2);
	}
}

void func3(int i) {
	puts("in func3");

	if(3 == i) {
		longjmp(env, 3);
	}
}

int main(int argc, char *argv[]) {
	switch(setjmp(env)) {
	case 0:
		puts("you can see this");
		func1(atoi(argv[1]));
		func2(atoi(argv[1]));
		func3(atoi(argv[1]));
		puts("never see this");
		break;
	case 1:
		puts("catch an exception1");
		break;
	case 2:
		puts("catch an exception2");
		break;
	case 3:
		puts("catch an exception3");
		break;
	default:
		puts("default");
	}

	puts("finally");

	return 0;
}
