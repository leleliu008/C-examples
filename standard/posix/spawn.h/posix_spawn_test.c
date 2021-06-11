#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>

extern char **environ;

int stub_system(const char* cmd) {
    char* const argv[] = {(char*)"sh", (char*)"-c", (char*)cmd, NULL};
    
    pid_t pid;
    int status;
    status = posix_spawn(&pid, "/bin/sh", NULL, NULL, argv, environ);
    if (0 == status) {
        return waitpid(pid, &status, 0);
    }
    return status;
}

int main(int argc, char* argv[]) {
    return stub_system(argv[1]);
}
