/* main函数参数测试 */

#include<stdio.h>

int main(int argc, char *argv[], char *env[]) {
	int i = 0;
	while (NULL != env[i]) {
		printf("%s\n", env[i]);
		i++;
	}
	return 0;
}
