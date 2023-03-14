#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/utsname.h>

#include "sysinfo.h"

#if defined (__APPLE__)
#include <regex.h>
#endif

int sysinfo_kind(char * buf, size_t bufSize) {
#if defined (_WIN32)
    strncpy(buf, "windows", bufSize > 7 ? 7 : bufSize);
    return 0;
#elif defined (__APPLE__)
    strncpy(buf, "darwin", bufSize > 6 ? 6 : bufSize);
    return 0;
#elif defined (__FreeBSD__)
    strncpy(buf, "freebsd", bufSize > 7 ? 7 : bufSize);
    return 0;
#elif defined (__OpenBSD__)
    strncpy(buf, "openbsd", bufSize > 7 ? 7 : bufSize);
    return 0;
#elif defined (__NetBSD__)
    strncpy(buf, "netbsd", bufSize > 6 ? 6 : bufSize);
    return 0;
#elif defined (__ANDROID__)
    strncpy(buf, "android", bufSize > 7 ? 7 : bufSize);
    return 0;
#elif defined (__linux__)
    strncpy(buf, "linux", bufSize > 5 ? 5 : bufSize);
    return 0;
#else
    struct utsname uts;

    if (uname(&uts) < 0) {
        return -1;
    }

    size_t osKindLength = strlen(uts.sysname);
    size_t n = bufSize > osKindLength ? osKindLength : bufSize;

    strncpy(buf, uts.sysname, n);

    for (size_t i = 0; i < n; i++) {
        if ((buf[i] >= 'A') && (buf[i] <= 'Z')) {
             buf[i] += 32;
        }
    }

    return 0;
#endif
}

int sysinfo_type(char * buf, size_t bufSize) {
#if defined (_WIN32)
    strncpy(buf, "windows", bufSize > 7 ? 7 : bufSize);
    return 0;
#elif defined (__APPLE__)
    strncpy(buf, "macos", bufSize > 5 ? 5 : bufSize);
    return 0;
#elif defined (__FreeBSD__)
    strncpy(buf, "freebsd", bufSize > 7 ? 7 : bufSize);
    return 0;
#elif defined (__OpenBSD__)
    strncpy(buf, "openbsd", bufSize > 7 ? 7 : bufSize);
    return 0;
#elif defined (__NetBSD__)
    strncpy(buf, "netbsd", bufSize > 6 ? 6 : bufSize);
    return 0;
#elif defined (__ANDROID__)
    strncpy(buf, "android", bufSize > 7 ? 7 : bufSize);
    return 0;
#elif defined (__linux__)
    strncpy(buf, "linux", bufSize > 5 ? 5 : bufSize);
    return 0;
#else
    struct utsname uts;

    if (uname(&uts) < 0) {
        return -1;
    }

    size_t osKindLength = strlen(uts.sysname);
    size_t n = bufSize > osKindLength ? osKindLength : bufSize;

    strncpy(buf, uts.sysname, n);

    for (size_t i = 0; i < n; i++) {
        if ((buf[i] >= 'A') && (buf[i] <= 'Z')) {
             buf[i] += 32;
        }
    }

    return 0;
#endif
}

int sysinfo_arch(char * buf, size_t bufSize) {
    struct utsname uts;

    if (uname(&uts) < 0) {
        return -1;
    }

    size_t osArchLength = strlen(uts.machine);

    strncpy(buf, uts.machine, bufSize > osArchLength ? osArchLength : bufSize);

    return 0;
}

int sysinfo_code(char * buf, size_t bufSize) {
#if defined (_WIN32)
    strncpy(buf, "windows", bufSize > 7 ? 7 : bufSize);
    return 0;
#elif defined (__APPLE__)
    strncpy(buf, "macos", bufSize > 5 ? 5 : bufSize);
    return 0;
#elif defined (__FreeBSD__)
    strncpy(buf, "freebsd", bufSize > 7 ? 7 : bufSize);
    return 0;
#elif defined (__OpenBSD__)
    strncpy(buf, "openbsd", bufSize > 7 ? 7 : bufSize);
    return 0;
#elif defined (__NetBSD__)
    strncpy(buf, "netbsd", bufSize > 6 ? 6 : bufSize);
    return 0;
#elif defined (__ANDROID__)
    strncpy(buf, "android", bufSize > 7 ? 7 : bufSize);
    return 0;
#else
    const char * filepath = "/etc/os-release";
    struct stat sb;

    if ((stat(filepath, &sb) == 0) && (S_ISREG(sb.st_mode) || S_ISLNK(sb.st_mode))) {
        FILE * file = fopen(filepath, "r");

        if (file == NULL) {
            return -1;
        }

        char line[50];

        for (;;) {
            if (fgets(line, 50, file) == NULL) {
                if (ferror(file)) {
                    perror(filepath);
                    fclose(file);
                    return -1;
                } else {
                    fclose(file);
                    return -1;
                }
            }

            if (strncmp(line, "ID=", 3) == 0) {
                char * p = &line[3];

                if (p[0] == '"' || p[0] == '\'') {
                    p++;
                }

                size_t n = strlen(p);

                p[n - 1] = '\0';
                n--;

                if (p[n - 1] == '"' || p[n - 1] == '\'') {
                    p[n - 1] = '\0';
                    n--;
                }

                strncpy(buf, p, bufSize > n ? n : bufSize);

                fclose(file);

                return 0;
            }
        }
    }

    return -1;
#endif
}

int sysinfo_name(char * buf, size_t bufSize) {
#if defined (_WIN32)
    strncpy(buf, "Windows", bufSize > 7 ? 7 : bufSize);
    return 0;
#elif defined (__APPLE__)
    strncpy(buf, "macOS", bufSize > 5 ? 5 : bufSize);
    return 0;
#elif defined (__FreeBSD__)
    strncpy(buf, "FreeBSD", bufSize > 7 ? 7 : bufSize);
    return 0;
#elif defined (__OpenBSD__)
    strncpy(buf, "OpenBSD", bufSize > 7 ? 7 : bufSize);
    return 0;
#elif defined (__NetBSD__)
    strncpy(buf, "NetBSD", bufSize > 6 ? 6 : bufSize);
    return 0;
#elif defined (__ANDROID__)
    strncpy(buf, "Android", bufSize > 7 ? 7 : bufSize);
    return 0;
#else
    const char * filepath = "/etc/os-release";
    struct stat sb;

    if ((stat(filepath, &sb) == 0) && (S_ISREG(sb.st_mode) || S_ISLNK(sb.st_mode))) {
        FILE * file = fopen(filepath, "r");

        if (file == NULL) {
            return -1;
        }

        char line[50];

        for (;;) {
            if (fgets(line, 50, file) == NULL) {
                if (ferror(file)) {
                    perror(filepath);
                    fclose(file);
                    return -1;
                } else {
                    fclose(file);
                    return -1;
                }
            }

            if (strncmp(line, "NAME=", 5) == 0) {
                char * p = &line[5];

                if (p[0] == '"' || p[0] == '\'') {
                    p++;
                }

                size_t n = strlen(p);

                p[n - 1] = '\0';
                n--;

                if (p[n - 1] == '"' || p[n - 1] == '\'') {
                    p[n - 1] = '\0';
                    n--;
                }

                strncpy(buf, p, bufSize > n ? n : bufSize);

                fclose(file);

                return 0;
            }
        }
    }

    return -1;
#endif
}

int sysinfo_vers(char * buf, size_t bufSize) {
#if defined (__NetBSD__) || defined (__OpenBSD__)
    struct utsname uts;

    if (uname(&uts) < 0) {
        return -1;
    }

    size_t n = strlen(uts.release);

    strncpy(buf, uts.release, bufSize > n ? n : bufSize);

    return 0;
#elif defined (__APPLE__)
    const char * filepath = "/System/Library/CoreServices/SystemVersion.plist";
    struct stat sb;

    if ((stat(filepath, &sb) == 0) && (S_ISREG(sb.st_mode) || S_ISLNK(sb.st_mode))) {
        FILE * file = fopen(filepath, "r");

        if (file == NULL) {
            return -1;
        }

        char line[512];

        for (;;) {
            if (fgets(line, 512, file) == NULL) {
                if (ferror(file)) {
                    perror(filepath);
                    fclose(file);
                    return -1;
                } else {
                    fclose(file);
                    return -1;
                }
            }

            regex_t regex;

            if (regcomp(&regex, "ProductVersion", REG_EXTENDED) != 0) {
                regfree(&regex);
                fclose(file);
                return -1;
            }

            regmatch_t regmatch[2];

            if (regexec(&regex, line, 2, regmatch, 0) != 0) {
                regfree(&regex);
                continue;
            }

            //printf("regmatch[0].rm_so=%d\n", regmatch[0].rm_so);
            //printf("regmatch[0].rm_eo=%d\n", regmatch[0].rm_eo);
            if (regmatch[0].rm_so >= 0 && regmatch[0].rm_eo > regmatch[0].rm_so) {
                regfree(&regex);

                if (fgets(line, 512, file) == NULL) {
                    if (ferror(file)) {
                        perror(filepath);
                        fclose(file);
                        return -1;
                    } else {
                        fclose(file);
                        return -1;
                    }
                }

                regex_t regex;

                if (regcomp(&regex, "[1-9][0-9.]+[0-9]", REG_EXTENDED) != 0) {
                    regfree(&regex);
                    fclose(file);
                    return -1;
                }

                regmatch_t regmatch[2];

                if (regexec(&regex, line, 2, regmatch, 0) != 0) {
                    regfree(&regex);
                    fclose(file);
                    return -1;
                }

                //printf("regmatch[0].rm_so=%d\n", regmatch[0].rm_so);
                //printf("regmatch[0].rm_eo=%d\n", regmatch[0].rm_eo);
                if (regmatch[0].rm_so >= 0 && regmatch[0].rm_eo > regmatch[0].rm_so) {
                    int n = regmatch[0].rm_eo - regmatch[0].rm_so;

                    strncpy(buf, line + regmatch[0].rm_so, bufSize > n ? n : bufSize);

                    regfree(&regex);
                    fclose(file);
                    return 0;
                } else {
                    regfree(&regex);
                    fclose(file);
                    return -1;
                }
            } else {
                regfree(&regex);
            }
        }
    }

    return -1;
#else
    const char * filepath = "/etc/os-release";
    struct stat sb;

    if ((stat(filepath, &sb) == 0) && (S_ISREG(sb.st_mode) || S_ISLNK(sb.st_mode))) {
        FILE * file = fopen(filepath, "r");

        if (file == NULL) {
            return -1;
        }

        char line[50];

        for (;;) {
            if (fgets(line, 50, file) == NULL) {
                if (ferror(file)) {
                    perror(filepath);
                    fclose(file);
                    return -1;
                } else {
                    fclose(file);
                    strncpy(buf, "rolling", bufSize > 7 ? 7 : bufSize);
                    return 0;
                }
            }

            if (strncmp(line, "VERSION_ID=", 11) == 0) {
                char * p = &line[11];

                if (p[0] == '"' || p[0] == '\'') {
                    p++;
                }

                size_t n = strlen(p);

                p[n - 1] = '\0';
                n--;

                if (p[n - 1] == '"' || p[n - 1] == '\'') {
                    p[n - 1] = '\0';
                    n--;
                }

                strncpy(buf, p, bufSize > n ? n : bufSize);

                fclose(file);

                return 0;
            }
        }
    }

    return -1;
#endif
}

int sysinfo_libc() {
    struct utsname uts;

    if (uname(&uts) < 0) {
        return -1;
    }

    if (strcmp(uts.sysname, "Linux") == 0) {
        size_t osArchLength = strlen(uts.machine);

        struct stat sb;

        if (strcmp(uts.machine, "x86_64") == 0) {
            if ((stat("/lib64/ld-linux-x86-64.so.2", &sb) == 0) && (S_ISREG(sb.st_mode) || S_ISLNK(sb.st_mode))) {
                return 1;
            }

            if ((stat("/lib/ld-musl-x86_64.so.1", &sb) == 0) && (S_ISREG(sb.st_mode) || S_ISLNK(sb.st_mode))) {
                return 2;
            }
        }

        if (strcmp(uts.machine, "ppc64le") == 0) {
            if ((stat("/lib/powerpc64le-linux-gnu/ld64.so.2", &sb) == 0) && (S_ISREG(sb.st_mode) || S_ISLNK(sb.st_mode))) {
                return 1;
            }

            if ((stat("/lib/ld-musl-powerpc64le.so.1", &sb) == 0) && (S_ISREG(sb.st_mode) || S_ISLNK(sb.st_mode))) {
                return 2;
            }
        }

        size_t   muslDynamicLoaderPathLength = osArchLength + 19;
        char     muslDynamicLoaderPath[muslDynamicLoaderPathLength];
        snprintf(muslDynamicLoaderPath, muslDynamicLoaderPathLength, "/lib/ld-musl-%s.so.1", uts.machine);

        if ((stat(muslDynamicLoaderPath, &sb) == 0) && (S_ISREG(sb.st_mode) || S_ISLNK(sb.st_mode))) {
            return 2;
        }

        size_t   dynamicLoaderPathLength = osArchLength + 22;
        char     dynamicLoaderPath[dynamicLoaderPathLength];
        snprintf(dynamicLoaderPath, dynamicLoaderPathLength, "/lib64/ld-linux-%s.so.2", uts.machine);

        if ((stat(dynamicLoaderPath, &sb) == 0) && (S_ISREG(sb.st_mode) || S_ISLNK(sb.st_mode))) {
            return 1;
        }
    }

    return 0;
}

int sysinfo_ncpu() {
    long nprocs;

#if defined (_SC_NPROCESSORS_ONLN)
    nprocs = sysconf(_SC_NPROCESSORS_ONLN);

    if (nprocs > 0) {
        return nprocs;
    }
#endif

#if defined (_SC_NPROCESSORS_CONF)
    nprocs = sysconf(_SC_NPROCESSORS_CONF);

    if (nprocs > 0) {
        return nprocs;
    }
#endif

    nprocs = 1;
    return nprocs;
}

int sysinfo_make(SysInfo * sysinfo) {
    if (sysinfo == NULL) {
        errno = EINVAL;
        return -1;
    }

    int ret;

    ///////////////////////////////////////

    char osArch[31] = {0};

    ret = sysinfo_arch(osArch, 30);

    if (ret != 0) {
        return ret;
    }

    ///////////////////////////////////////

    char osKind[31] = {0};

    ret = sysinfo_kind(osKind, 30);

    if (ret != 0) {
        return ret;
    }

    ///////////////////////////////////////

    char osType[31] = {0};

    ret = sysinfo_type(osType, 30);

    if (ret != 0) {
        return ret;
    }

    ///////////////////////////////////////

    char osCode[31] = {0};

    ret = sysinfo_code(osCode, 30);

    if (ret != 0) {
        return ret;
    }

    ///////////////////////////////////////

    char osName[31] = {0};

    ret = sysinfo_name(osName, 30);

    if (ret != 0) {
        return ret;
    }

    ///////////////////////////////////////

    char osVers[31] = {0};

    ret = sysinfo_vers(osVers, 30);

    if (ret != 0) {
        return ret;
    }

    ///////////////////////////////////////

    int libc = sysinfo_libc();

    if (libc < 0) {
        return libc;
    }

    ///////////////////////////////////////

    int ncpu = sysinfo_ncpu();

    if (ncpu < 0) {
        return ncpu;
    }

    ///////////////////////////////////////

    sysinfo->arch = strdup(osArch);

    if (sysinfo->arch == NULL) {
        sysinfo_free(*sysinfo);
        errno = ENOMEM;
        return -1;
    }

    sysinfo->kind = strdup(osKind);

    if (sysinfo->kind == NULL) {
        sysinfo_free(*sysinfo);
        errno = ENOMEM;
        return -1;
    }

    sysinfo->type = strdup(osType);

    if (sysinfo->type == NULL) {
        sysinfo_free(*sysinfo);
        errno = ENOMEM;
        return -1;
    }

    sysinfo->code = strdup(osCode);

    if (sysinfo->code == NULL) {
        sysinfo_free(*sysinfo);
        errno = ENOMEM;
        return -1;
    }

    sysinfo->name = strdup(osName);

    if (sysinfo->name == NULL) {
        sysinfo_free(*sysinfo);
        errno = ENOMEM;
        return -1;
    }

    sysinfo->vers = strdup(osVers);

    if (sysinfo->vers == NULL) {
        sysinfo_free(*sysinfo);
        errno = ENOMEM;
        return -1;
    }

    sysinfo->libc = libc;
    sysinfo->ncpu = ncpu;

    sysinfo->euid = geteuid();
    sysinfo->egid = getegid();

    return 0;
}

void sysinfo_dump(SysInfo sysinfo) {
    printf("sysinfo.ncpu: %u\n",  sysinfo.ncpu);
    printf("sysinfo.arch: %s\n",  sysinfo.arch == NULL ? "" : sysinfo.arch);
    printf("sysinfo.kind: %s\n",  sysinfo.kind == NULL ? "" : sysinfo.kind);
    printf("sysinfo.type: %s\n",  sysinfo.type == NULL ? "" : sysinfo.type);
    printf("sysinfo.code: %s\n",  sysinfo.code == NULL ? "" : sysinfo.code);
    printf("sysinfo.name: %s\n",  sysinfo.name == NULL ? "" : sysinfo.name);
    printf("sysinfo.vers: %s\n",  sysinfo.vers == NULL ? "" : sysinfo.vers);
    printf("sysinfo.euid: %u\n",  sysinfo.euid);
    printf("sysinfo.egid: %u\n",  sysinfo.egid);

    switch(sysinfo.libc) {
        case 1:  printf("sysinfo.libc: glibc\n"); break;
        case 2:  printf("sysinfo.libc: musl\n");  break;
        default: printf("sysinfo.libc: \n");
    }
}

void sysinfo_free(SysInfo sysinfo) {
    if (sysinfo.arch != NULL) {
        free(sysinfo.arch);
        sysinfo.arch = NULL;
    }

    if (sysinfo.kind != NULL) {
        free(sysinfo.kind);
        sysinfo.kind = NULL;
    }

    if (sysinfo.type != NULL) {
        free(sysinfo.type);
        sysinfo.type = NULL;
    }

    if (sysinfo.code != NULL) {
        free(sysinfo.code);
        sysinfo.code = NULL;
    }

    if (sysinfo.name != NULL) {
        free(sysinfo.name);
        sysinfo.name = NULL;
    }

    if (sysinfo.vers != NULL) {
        free(sysinfo.vers);
        sysinfo.vers = NULL;
    }
}
