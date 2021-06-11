#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main() {
	int server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == server_socket_fd) {
		perror("create socket error!");
		goto label;
	}

	printf("socket create!\n");

	struct sockaddr_in server_socket_address;

	/* 设置协议族 - ipv4 */
	server_socket_address.sin_family = AF_INET;
	
	/* 设置地址 - 让系统自动获取本机IP地址 */
	server_socket_address.sin_addr.s_addr = htonl(INADDR_ANY);
	
	/* 设置端口 */
	server_socket_address.sin_port = htons(8000);

	/* 绑定端口 */
	if(-1 == bind(server_socket_fd, (struct sockaddr*)&server_socket_address, sizeof(server_socket_address))) {
		perror("bind error!");
		goto label;
	}

	printf("socket bounded!\n");

	/* 开始监听端口，并设置最大连接数为100 */
	if(-1 == listen(server_socket_fd, 100)) {
		perror("listen error!");
		goto label;
	}

	printf("listen port 8000!\n");

	while(1) {
		/* accept可能会阻塞，以等待客户端的连接 */
		int client_socket_fd = accept(server_socket_fd, NULL, NULL);
		if(-1 == client_socket_fd) {
			perror("accept error!");
			continue;
		}

		printf("accept client socket %d\n", client_socket_fd);
		
		char buff[4096];
		if(-1 == read(client_socket_fd, buff, sizeof(buff))) {
			perror("read client socket error!");
			continue;
		}
		
		printf("from client message : %s\n", buff);

		char str[] = "I love you, too!";
		if(-1 == write(client_socket_fd, str, sizeof(str))) {
			perror("write client socket error!");
			continue;
		}
		
		printf("send message back : %s\n", str);

		close(client_socket_fd);
	}

label:
	close(server_socket_fd);
	return 0;
}
