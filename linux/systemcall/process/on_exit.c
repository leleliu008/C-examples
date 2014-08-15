#include<stdlib.h>
#include<stdio.h>

static void onexit(int status, void *arg) {
	printf("onexit");
	printf("status = %d\n", status);
	printf("arg = %s\n", (char*) arg);
}

int main() {
	char *p = "Bye bye!";
	if(0 != on_exit(onexit, p)) {
	
	}
	return 100;
}
