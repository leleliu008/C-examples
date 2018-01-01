#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>

int main() {
	int c_socket_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
	if(-1 == c_socket_fd) {
		perror("socket create error!");
		goto label;
	}

	printf("socket create success!\n");

	struct sockaddr_un server_address;

	/* 将server_address所占内存全部用0填充 */
	memset(&server_address, 0, sizeof(server_address));

	server_address.sun_family = AF_LOCAL;

	/* 将一个抽象的名字复制到sun_path的第二个字节处 */
	strcpy(&server_address.sun_path[1], "com.leleliu008.localsockettest");

	if(-1 == connect(c_socket_fd, (struct sockaddr*)&server_address, \
							      sizeof(server_address))) {
		perror("socket connect error! errno");
		printf("errno = %d\n", errno);
		goto label;
	}

	printf("socket connect success!\n");

	char str[] = "I love you!";
	if(-1 == write(c_socket_fd, str, sizeof(str))) {
		perror("write error!");
		goto label;
	}

	printf("send message to server : %s\n", str);

	char buff[4098] = {'\0'};
	if(-1 == read(c_socket_fd, buff, sizeof(buff))) {
		perror("read error!");
		goto label;
	}

	printf("reveive message from server : %s\n", buff);

label:
	close(c_socket_fd);
	return 0;
}
