#include <string.h>
#include <errno.h>

int main() {
    char buff[100];

    #if defined (__USE_GNU) && __ANDROID_API__ >= 23
        char *ret = __gnu_strerror_r(ERANGE, buff sizeof(buff));
        return 1;
    #else
        int ret = strerror_r (ERANGE, buff, sizeof(buff));
        return ret;
    #endif
}
