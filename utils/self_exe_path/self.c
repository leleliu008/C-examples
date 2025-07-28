#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/stat.h>

// https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/dyld.3.html
#if defined (__APPLE__)
#include <mach-o/dyld.h>
#include <sys/syslimits.h>
#elif defined (__linux__) && defined (HAVE_LINUX_LIMITS_H)
#include <linux/limits.h>
#else
#include <limits.h>
#endif

#if defined (__NetBSD__) || defined (__OpenBSD__) || defined (__FreeBSD__) || defined (__DragonFly__)
#include <sys/types.h>
#include <sys/sysctl.h>
#endif

#include "self.h"

int selfpath(char buf[]) {
#if defined (__APPLE__)
    // https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/dyld.3.html
    uint32_t bufSize = 0U;
    _NSGetExecutablePath(NULL, &bufSize);
    _NSGetExecutablePath(buf,  &bufSize);

    return (bufSize - 1);
#elif defined (__FreeBSD__) || defined (__DragonFly__)
    const int mib[] = { CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, -1 };

    size_t len = 0U;

    if (sysctl(mib, 4, NULL, &len, NULL, 0) < 0) {
        return -1;
    }

    if (sysctl(mib, 4, buf,  &len, NULL, 0) < 0) {
        return -1;
    }

    return len;
#elif defined (__NetBSD__)
    const int mib[] = { CTL_KERN, KERN_PROC_ARGS, -1, KERN_PROC_PATHNAME };

    size_t len = 0U;

    if (sysctl(mib, 4, NULL, &len, NULL, 0) < 0) {
        return -1;
    }

    if (sysctl(mib, 4, buf,  &len, NULL, 0) < 0) {
        return -1;
    }

    return len;
#elif defined (__OpenBSD__)
    const int mib[4] = { CTL_KERN, KERN_PROC_ARGS, getpid(), KERN_PROC_ARGV };

    size_t size;

    if (sysctl(mib, 4, NULL, &size, NULL, 0) != 0) {
        return -1;
    }

    char** argv = (char**)malloc(size);

    if (argv == NULL) {
        errno = ENOMEM;
        return -1;
    }

    memset(argv, 0, size);

    if (sysctl(mib, 4, argv, &size, NULL, 0) != 0) {
        return -1;
    }

    //////////////////////////////////

    size_t m = 0U;

    int ispath = 0;

    for ( ; argv[0][m] != '\0'; m++) {
        if (argv[0][m] == '/') {
            ispath = 1;
        }
    }

    char argv0[m];

    for (size_t j = 0U; j <= m; j++) {
        argv0[j] = argv[0][j];
    }

    free(argv);

    //////////////////////////////////

    if (ispath == 1) {
        if (realpath(argv0, buf) == NULL) {
            return -1;
        } else {
            return 0;
        }
    }

    //////////////////////////////////

    const char * p = getenv("PATH");

    if (p == NULL) {
        return -2;
    }

    if (p[0] == '\0') {
        return -3;
    }

    //////////////////////////////////

    struct stat st;

    char pathBuf[PATH_MAX];

    char * q;

    size_t i;
    size_t n;

loop:
    if (p[0] == '\0') {
        return 0;
    }

    if (p[0] == ' ' || p[0] == ':') {
        p++;
        goto loop;
    }

    //////////////////////////////////

    for (i = 0U; ; i++) {
        pathBuf[i] = p[i];

        if (p[i] == '\0') {
            break;
        }

        if (p[i] == ':') {
            pathBuf[i] = '\0';
            break;
        }
    }

    //////////////////////////////////

    if ((stat(pathBuf, &st) == 0) && S_ISDIR(st.st_mode)) {
        q = &pathBuf[i];

        q[0] = '/';

        q++;

        for (size_t j = 0U; ; j++) {
            q[j] = argv0[j];

            if (q[j] == '\0') {
                n = i + j + 1U;
                break;
            }
        }

        if (access(pathBuf, X_OK) == 0) {
            for (size_t j = 0U; j < n; j++) {
                buf[j] = pathBuf[j];
            }

            buf[n] = '\0';

            return n;
        }
    }

    //////////////////////////////////

    p += i;

    if (p[0] == ':') {
        p++;
        goto loop;
    }

    return 0;
#else
    ssize_t n = readlink("/proc/self/exe", buf, PATH_MAX - 1);

    // readlink() does not append a terminating null byte to buf.
    if (n > 0) {
        buf[n] = '\0';
    }

    return n;
#endif
}
