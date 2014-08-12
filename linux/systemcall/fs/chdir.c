#include<unistd.h>
#include<errno.h>
#include<stdio.h>

int main(int argc, char *argv[]) {
	if(2 != argc) {
		perror("请输入一个文件夹的绝对路径");
		return 0;
	}

	char buff[1024];
	getcwd(buff, sizeof(buff));
	printf("current working dir is %s\n", buff);

	int rc = chdir(argv[1]);
	if(0 == rc) {
		printf("change dir to %s\n", argv[1]);

		getcwd(buff, sizeof(buff));
		printf("current working dir is %s\n", buff);
	} else if(-1 == rc) {
		extern int errno;
		if(EACCES == errno) {
			perror("没有权限");
		} else if(EFAULT == errno) {
			perror("path参数的地址非法");
		} else if(EIO == errno) {
			perror("I/O错误");
		} else if(ELOOP == errno) {
			perror("解析路径中有太多的符号链接");
		} else if(ENAMETOOLONG == errno) {
			perror("路径过长");
		} else if(ENOMEM == errno) {
			perror("内存不足");
		} else if(ENOENT == errno) {
			perror("文件不存在");
		} else if(ENOTDIR == errno) {
			perror("不是文件夹");
		} else {
			perror("未知原因");
		}
	}

	return 0;
}
