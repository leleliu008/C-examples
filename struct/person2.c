#include<stdbool.h>

struct person {
	char *name;
	unsigned short age;
	char sex;
	bool issingle;
	float weight;
};

#include<stdio.h>

int main() {
	struct person person1 = {"WangHua", 18u, 'F', true, 120.0f};
	struct person person2 = {.name = "WangHua", .age = 18u, .sex = 'F', .issingle = true, .weight = 120.0f};
	struct person person3 = {name : "WangHua", age : 18u, sex : 'F', issingle : true, weight : 120.0f};
	struct person person4;
	person4.name = "WangHua";
	person4.age = 18u;
	person4.sex = 'F';
	person4.issingle = true;
	person4.weight = 120.0f;
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
	printf("---------------------\n");
	printf("person3.name = %s\n", person3.name);
	printf("preson3.age = %u\n", person3.age);
	printf("perosn3.sex = %c\n", person3.sex);
	printf("person3.issingle = %d\n", person3.issingle);
	printf("person3.weight = %f\n", person3.weight);
	printf("---------------------\n");
	printf("person4.name = %s\n", person4.name);
	printf("preson4.age = %u\n", person4.age);
	printf("perosn4.sex = %c\n", person4.sex);
	printf("person4.issingle = %d\n", person4.issingle);
	printf("person4.weight = %f\n", person4.weight);
	return 0;
}
