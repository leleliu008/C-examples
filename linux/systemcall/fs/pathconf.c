#include<unistd.h>
#include<errno.h>
#include<stdio.h>

int main(int argc, char *argv[]) {
	if(argc != 3) {
		perror("请输入一个序号和一个路径");
		return 0;
	}
	
	int index = atoi(argv[2]);
	if(index < 0 || index >= 9) {
		perror("第二个参数必须是小于9的非负整数");
		return 0;
	}

	char *namestr[] = {"_PC_LINK_MAX", "_PC_MAX_CANON", \
			           "_PC_MAX_INPUT", "_PC_NAME_MAX", \
			           "_PC_PATH_MAX", "_PC_PIPE_BUF", \
			           "_PC_CHOWN_RESTRICTED", \
			           "_PC_NO_TRUNC", "_PC_VDISABLE"};

	int name[] = {_PC_LINK_MAX, _PC_MAX_CANON, \
			      _PC_MAX_INPUT, _PC_NAME_MAX, \
	              _PC_PATH_MAX, _PC_PIPE_BUF,  \
	              _PC_CHOWN_RESTRICTED, \
				  _PC_NO_TRUNC, _PC_VDISABLE};

	long limit = pathconf(argv[1], name[index]);

	if(limit < 0) {
		extern int errno;
		if(EACCES == errno) {
			perror("没有权限访问");
		} else if(EINVAL == errno) {
			perror("name参数无效");
		} else if(ELOOP == errno) {
			perror("嵌套层次太多");
		} else if(ENAMETOOLONG == errno) {
			perror("path参数太长了");
		} else if(ENOENT == errno) {
			perror("文件不存在");
		} else if(ENOSYS == errno) {
			perror("无限制");
		} else if(ENOTDIR == errno) {
			perror("不是一个目录");
		}
	} else {
		printf("pathconf(\"%s\", %s) = %ld\n", \
				argv[1], namestr[index], limit);
	}
	return 0;
}
