#include<unistd.h>

int main() {
	pid_t ppid = getppid();
	pid_t pid = getpid();

	pid_t pgid0 = getpgid(ppid);
	pid_t pgid1 = getpgid(pid);
	pid_t pgid2 = getpgid(0);

	setpgid(pid, ppid);
	
	pid_t pgid3 = getpgid(ppid);
	pid_t pgid4 = getpgid(pid);
	
	return 0;
}
