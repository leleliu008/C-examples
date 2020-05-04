#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char* argv[]) {
    if (1 == argc) {
        perror("please provide a library path");
        return 1;
    }

    void* handle = dlopen(argv[1], RTLD_LAZY);
    if (NULL == handle) {
        printf("load %s error, %s\n", argv[1], dlerror());
        return 1;
    }

    int (*add)(int a, int b);
    add = dlsym(handle, "add");
    int value = add(2, 3);
    printf("load %s success.\n", argv[1]);
    printf("add(2, 3) = %d\n", value);

    int statusCode = dlclose(handle);
    printf("unload %s %s!\n", argv[1], statusCode ? "failed" : "success");
    return statusCode;
}
