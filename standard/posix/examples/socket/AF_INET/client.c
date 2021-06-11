#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main() {
	int c_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == c_socket_fd) {
		perror("socket create error!");
		goto label;
	}

	printf("socket create success!\n");

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(8000);

	if(-1 == connect(c_socket_fd, (struct sockaddr*)&server_address, sizeof(server_address))) {
		perror("socket connect error!");
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
