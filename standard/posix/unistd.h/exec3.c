#include<unistd.h>
#include<stdio.h>

int main() {
	pid_t pid = fork();
	if(pid < 0) {
		perror("fork error!");
	} else if(0 == pid) {
		if(execl("/bin/echo", "", "executed by execl!", NULL) < 0) {
			perror("execl error!");
		}
	}
	return 0;
}

