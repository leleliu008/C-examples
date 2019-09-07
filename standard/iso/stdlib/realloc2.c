#include<stdlib.h>

int main() {
	char *p, *q, *r;
	p = (char*) malloc(10 * sizeof(char));
	r = (char*) malloc(10 * sizeof(char));
	q = (char*) realloc(p, 30);
	
	if(NULL == q) {
		free(p);
	} else {
		free(q);
	}
	
	return 0;
}
