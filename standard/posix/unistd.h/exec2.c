#include<unistd.h>
#include<stdio.h>

int main() {
	if (execl("/bin/ls", "", NULL) < 0) {
		perror("execl error!");
	}
    //下面的代码根本不会被执行，因为exec系列的函数会用被执行命令的进程替换掉当前的进程，exec函数调用后面的代码无法被执行
    //通过观察这个现象，更能理解exec系列函数的特性
	printf("execl success!\n");
	return 0;
}

