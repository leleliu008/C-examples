#include<stdbool.h>

typedef struct {
	char *name;
	unsigned short age;
	char sex;
	bool issingle;
	float weight;
} Person;

#include<stdio.h>

int main() {
	printf("sizeof(Person) = %lu\n", sizeof(Person));

	return 0;
}
