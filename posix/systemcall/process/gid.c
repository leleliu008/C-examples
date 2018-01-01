#include<unistd.h>

int main() {
	gid_t gid = getgid();
	gid_t egid = getegid();
	return 0;
}
