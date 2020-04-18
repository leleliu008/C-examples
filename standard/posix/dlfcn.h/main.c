#include <stdio.h>
#include <dlfcn.h>

int main(int argc __attribute((__unused__)), char* argv[] __attribute__((__unused__))) {
    void* handle = dlopen(LD_FILE_NAME, RTLD_LAZY);
    if (NULL == handle) {
        printf("load %s error, %s\n", LD_FILE_NAME, dlerror());
        return 1;
    }

    int (*add)(int a, int b);
    add = dlsym(handle, "add");
    int value = add(2, 3);
    printf("load %s success.\n", LD_FILE_NAME);
    printf("add(2, 3) = %d\n", value);

    int errorCode = dlclose(handle);
    if (errorCode) {
        printf("unload %s failed!\n", LD_FILE_NAME);
        return 1;
    } else {
        printf("unload %s success.\n", LD_FILE_NAME);
        return 0;
    }
}
