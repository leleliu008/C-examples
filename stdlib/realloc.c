#include<stdlib.h>

int main() {
	char *p, *q;
	p = (char*) malloc(10 * sizeof(char));
	q = (char*) realloc(p, 20);

	if(NULL == q) {
		free(p);
	} else {
		free(q);
	}

	return 0;
}
