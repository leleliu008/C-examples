struct person {
	char *name;
	unsigned short age;
	char sex;
	float weight;
} person1, person2, person3;

#include<stdio.h>

int main() {
	person1 = {"WangHua", 18u, 'F', 120.0f};
	person2 = {.name = "WangHua", .age = 18u, .sex = 'F', .weight = 120.0f};
	person3.name = "WangHua";
	person3.age = 18u;
	person3.sex = 'F';
	person3.weight = 120.0f;

	printf("person1.name = %s\n", person1.name);
	printf("preson1.age = %u\n", person1.age);
	printf("perosn1.sex = %c\n", person1.sex);
	printf("person1.weight = %f\n", person1.weight);
	printf("---------------------\n");
	printf("person2.name = %s\n", person2.name);
	printf("preson2.age = %u\n", person2.age);
	printf("perosn2.sex = %c\n", person2.sex);
	printf("person2.weight = %f\n", person2.weight);
	printf("---------------------\n");
	printf("person3.name = %s\n", person3.name);
	printf("preson3.age = %u\n", person3.age);
	printf("perosn3.sex = %c\n", person3.sex);
	printf("person3.weight = %f\n", person3.weight);

	return 0;
}
