typedef struct {
	char *name;
	unsigned short age;
	char sex;
	float weight;
	char issingle;
} Person;

typedef struct {
	char *name;
	char sex;
	char issingle;
	unsigned short age;
	float weight;
} person;

#include<stdio.h>

int main() {
	printf("sizeof(Person) = %lu\n", sizeof(Person));
	printf("sizeof(person) = %lu\n", sizeof(person));
	return 0;
}
