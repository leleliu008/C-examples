#include<stdbool.h>

typedef struct {
	char *name;
	unsigned short age;
	char sex;
	bool issingle;
	float weight;
} Person;

#include<stdio.h>
#include<stdlib.h>

int main() {
	Person person = {"WangHua", 18u, 'F', true, 120.0f};

	Person *p1 = &person;

	printf("p1->name = %s\n", p1->name);
	printf("p1->age = %u\n", p1->age);
	printf("p1->sex = %c\n", p1->sex);
	printf("p1->issingle = %d\n", p1->issingle);
	printf("p1->weight = %f\n", p1->weight);
	
	Person *p2 = (Person *)malloc(sizeof(Person));
	
	if(NULL != p2) {	
		(*p2).name = "WangHua";
		(*p2).age = 18u;
		(*p2).sex = 'F';
		(*p2).issingle = true;
		(*p2).weight = 120.0f;
	
		p2->name = "WangHua";
		p2->age = 18u;
		p2->sex = 'F';
		p2->issingle = true;
		p2->weight = 120.0f;

		printf("---------------------\n");
		printf("p2->name = %s\n", p2->name);
		printf("p2->age = %u\n", p2->age);
		printf("p2->sex = %c\n", p2->sex);
		printf("p2->issingle = %d\n", p2->issingle);
		printf("p2->weight = %f\n", p2->weight);

		free(p2);
	}

	return 0;
}
