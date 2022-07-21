#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int p[2];

    if (pipe(p) < 0) {
        perror("create a pipe failed");
        return 1;
    }

    write(p[1], "I", 2);

    char buff[1024] = {0};
    size_t size = 0;

    while ((size = read(p[0], buff, 1024)) != 0) {
        printf("%s\n", buff);
    }

    return 0;
}
