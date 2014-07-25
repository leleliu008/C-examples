#include<stdbool.h>

typedef struct {
	char *name;
	unsigned short age;
	char sex;
	bool issingle;
	float weight;
} Person;

typedef struct {
	char *name;
	unsigned short age;
	char sex;
	float weight;
	bool issingle;
} Person2;

#include<stdio.h>

int main() {
	printf("sizeof(Person) = %lu\n", sizeof(Person));
	printf("sizeof(Person2) = %lu\n", sizeof(Person2));

	Person person = {"WangHua", 18u, 'F', true, 120.0f};
	Person2 person2 = {"WangHua", 18u, 'F', 120.0f, true};

	return 0;
}
