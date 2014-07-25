#include<stdbool.h>

typedef struct person {
	char *name;
	unsigned short age;
	char sex;
	bool issingle;
	float weight;
} PERSON;

#include<stdio.h>

int main() {
	struct person person1 = {"WangHua", 18u, 'F', true, 120.0f};
	PERSON person2 = {"WangHua", 18u, 'F', true, 120.0f};

	printf("person1.name = %s\n", person1.name);
	printf("preson1.age = %u\n", person1.age);
	printf("perosn1.sex = %c\n", person1.sex);
	printf("person1.issingle = %d\n", person1.issingle);
	printf("person1.weight = %f\n", person1.weight);
	printf("---------------------\n");
	printf("person2.name = %s\n", person2.name);
	printf("preson2.age = %u\n", person2.age);
	printf("perosn2.sex = %c\n", person2.sex);
	printf("person2.issingle = %d\n", person2.issingle);
	printf("person2.weight = %f\n", person2.weight);
	
	return 0;
}
