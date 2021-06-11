#include <stdio.h>

int main(int argc, char** argv) {
    fprintf(stderr, "stderr argc = %d, %s\n", argc, argv[0]);
    fprintf(stdout, "stdout argc = %d, %s\n", argc, argv[0]);
    return 0;
}
