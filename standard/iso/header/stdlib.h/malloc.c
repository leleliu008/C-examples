#include<stdlib.h>
#include<string.h>

int main() {
	char * str = (char*) malloc(10 * sizeof(char));
	if(str) {
		strcpy(str, "Hello");
		free(str);
	}
	return 0;
}
