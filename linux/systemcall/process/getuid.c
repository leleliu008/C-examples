#include<unistd.h>

int main() {
	uid_t uid = getuid();
	uid_t euid = geteuid();
	return 0;
}
