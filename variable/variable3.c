/* 变量作用域 - 文件内的全局变量*/
#include"other.h"

int a = 20;

int main(int argc, char *argv[]) {
	int a = 10;
	other();
	return 0;
}
