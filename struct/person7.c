#include<stdbool.h>

#pragma pack(16)
typedef struct {
	char *name;
	unsigned short age;
	char sex;
	float weight;
	bool issingle;
} Person;

#include<stdio.h>
#include<stddef.h>

int main() {
	size_t size  = sizeof(Person);
	printf("sizeof(Person) = %lu\n", size);
	
	Person person = {"WangHua", 18u, 'F', 120.0f, true};

	return 0;
}
