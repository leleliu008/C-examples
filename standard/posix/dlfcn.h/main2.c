#include <stdio.h>

extern int add(int a, int b);

int main() {
    int value = add(2, 3);
    printf("add(2, 3) = %d\n", value);
    return 0;
}
