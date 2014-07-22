typedef struct {
	char *name;
	unsigned short age;
	char sex;
	float weight;
} Person;

#include<stdio.h>
#include<stdlib.h>

int main() {
	Person person = {"WangHua", 18u, 'F', 120.0f};
	
	Person *p1 = &person;

	Person *p2 = (Person *)malloc(sizeof(Person));
	
	(*p2).name = "WangHua";
	(*p2).age = 18u;
	(*p2).sex = 'F';
	(*p2).weight = 120.0f;
	
	p2->name = "WangHua";
	p2->age = 18u;
	p2->sex = 'F';
	p2->weight = 120.0f;

	printf("p1->name = %s\n", p1->name);
	printf("p1->age = %u\n", p1->age);
	printf("p1->sex = %c\n", p1->sex);
	printf("p1->weight = %f\n", p1->weight);
	printf("---------------------\n");
	printf("p2->name = %s\n", p2->name);
	printf("p2->age = %u\n", p2->age);
	printf("p2->sex = %c\n", p2->sex);
	printf("p2->weight = %f\n", p2->weight);
	
	return 0;
}
