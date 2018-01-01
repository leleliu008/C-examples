#include<stdbool.h>

typedef struct {
	char *name;
	unsigned short age;
	char sex;
	bool issingle;
	float weight;
} Person;

#include<stdio.h>

#define NUM 5

int main() {
	Person person[NUM];
	int i = 0;

	for(i = 0; i < NUM; i++) {
		//实际开发中，这里往往是连接数据库获取数据的
		person[i].name = "WangHua";
		person[i].age = 18u;
		person[i].sex = 'F';
		person[i].issingle = true;
		person[i].weight = 120.0f;
	}

	for(i = 0; i < NUM; i++) {
		printf("person[%d].name = %s\n", i, person[i].name);
		printf("preson[%d].age = %u\n", i, person[i].age);
		printf("perosn[%d].sex = %c\n", i, person[i].sex);
		printf("person[%d].issingle = %d\n", i, person[i].issingle);
		printf("person[%d].weight = %f\n", i, person[i].weight);
	}
	
	return 0;
}
