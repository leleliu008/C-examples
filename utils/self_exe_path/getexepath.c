#include <_stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/syslimits.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>

static int selfpath(char buf[], char * argv0, char * owd) {
    fprintf(stderr, "argv0=%s\nowd=%s\n", argv0, owd);

    //////////////////////////////////

    if (argv0[0] == '/') {
        for (int i = 0; ; i++) {
            buf[i] = argv0[i];

            if (buf[i] == '\0') {
                return i;
            }
        }
    }

    //////////////////////////////////

    for (int i = 0; argv0[i] != '\0'; i++) {
        if (argv0[i] == '/') {
            return snprintf(buf, PATH_MAX, "%s/%s", owd, argv0);
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
}

int main(__attribute__((unused)) int argc, char* argv[]) {
    char owd[PATH_MAX];

    if (getcwd(owd, PATH_MAX) == NULL) {
        perror(NULL);
        return -1;
    }

    if (chdir("/usr/local") == -1) {
        perror("/usr/local");
        return -1;
    }

    char buf[PATH_MAX];

    int ret = selfpath(buf, argv[0], owd);

    if (ret > 0) {
        char p[PATH_MAX];

        if (realpath(buf, p) == NULL) {
            perror(buf);
            return -1;
        }

        puts(p);
        return 0;
    }

    return ret;
}
