/* 变量作用域 - 全局变量*/

#include"other.c"

int a = 20;

int main(int argc, char *argv[]) {
	int a = 10;
	func();

	return 0;
}
