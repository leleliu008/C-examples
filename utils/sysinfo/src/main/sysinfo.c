#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sysinfo.h>

#define COLOR_GREEN  "\033[0;32m"
#define COLOR_OFF    "\033[0m"

static void showHelp() {
    if (isatty(STDOUT_FILENO)) {
        const char * str = "usage:\n\n"
        COLOR_GREEN
        "sysinfo --help\n"
        "sysinfo -h\n"
        COLOR_OFF
        "    show help of this command.\n\n"
        COLOR_GREEN
        "sysinfo --version\n"
        "sysinfo -V\n"
        COLOR_OFF
        "    show version of this command.\n\n"
        COLOR_GREEN
        "sysinfo kind\n"
        COLOR_OFF
        "    show the kind of your system.\n\n"
        COLOR_GREEN
        "sysinfo type\n"
        COLOR_OFF
        "    show the type of your system.\n\n"
        COLOR_GREEN
        "sysinfo code\n"
        COLOR_OFF
        "    show the code of your system.\n\n"
        COLOR_GREEN
        "sysinfo name\n"
        COLOR_OFF
        "    show the name of your system.\n\n"
        COLOR_GREEN
        "sysinfo vers\n"
        COLOR_OFF
        "    show the version of your system.\n\n"
        COLOR_GREEN
        "sysinfo arch\n"
        COLOR_OFF
        "    show the cpu arch of your system.\n\n"
        COLOR_GREEN
        "sysinfo ncpu\n"
        COLOR_OFF
        "    show the count of cpu core of your system.\n\n"
        COLOR_GREEN
        "sysinfo euid\n"
        COLOR_OFF
        "    show the effective user ID of your system.\n\n"
        COLOR_GREEN
        "sysinfo egid\n"
        COLOR_OFF
        "    show the effective group ID of your system.\n"
        ;

        printf("%s\n", str);
    } else {
        printf("%s\n",
            "usage:\n\n"
            "sysinfo --help\n"
            "sysinfo -h\n"
            "    show help of this command.\n\n"
            "sysinfo --version\n"
            "sysinfo -V\n"
            "    show version of this command.\n\n"
            "sysinfo kind\n"
            "    show the kind of your system.\n\n"
            "sysinfo type\n"
            "    show the type of your system.\n\n"
            "sysinfo code\n"
            "    show the code of your system.\n\n"
            "sysinfo name\n"
            "    show the name of your system.\n\n"
            "sysinfo vers\n"
            "    show the version of your system.\n\n"
            "sysinfo arch\n"
            "    show the cpu arch of your system.\n\n"
            "sysinfo ncpu\n"
            "    show the count of cpu core of your system.\n\n"
            "sysinfo euid\n"
            "    show the effective user ID of your system.\n\n"
            "sysinfo egid\n"
            "    show the effective group ID of your system.\n\n"
        );
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        SysInfo sysinfo = {0};

        int ret = sysinfo_make(&sysinfo);

        if (ret != 0) {
            perror(NULL);
            return ret;
        }

        sysinfo_dump(sysinfo);
        sysinfo_free(sysinfo);
       
        return 0;
    }

           if (strcmp(argv[1], "-h") == 0) {
        showHelp();
        return 0;
    } else if (strcmp(argv[1], "--help") == 0) {
        showHelp();
        return 0;
    } else if (strcmp(argv[1], "-V") == 0) {
        printf("%s\n", "1.0.0");
        return 0;
    } else if (strcmp(argv[1], "--version") == 0) {
        printf("%s\n", "1.0.0");
        return 0;
    } else if (strcmp(argv[1], "kind") == 0) {
        char osKind[31] = {0};

        int ret = sysinfo_kind(osKind, 20);

        if (ret != 0) {
            perror(NULL);
            return ret;
        }

        printf("%s\n", osKind);
        return 0;
    } else if (strcmp(argv[1], "type") == 0) {
        char osType[31] = {0};

        int ret = sysinfo_type(osType, 20);

        if (ret != 0) {
            perror(NULL);
            return ret;
        }

        printf("%s\n", osType);
        return 0;
    } else if (strcmp(argv[1], "arch") == 0) {
        char osArch[31] = {0};

        int ret = sysinfo_arch(osArch, 20);

        if (ret != 0) {
            perror(NULL);
            return ret;
        }

        printf("%s\n", osArch);
        return 0;
    } else if (strcmp(argv[1], "code") == 0) {
        char osCode[31] = {0};

        int ret = sysinfo_code(osCode, 20);

        if (ret != 0) {
            perror(NULL);
            return ret;
        }

        printf("%s\n", osCode);
        return 0;
    } else if (strcmp(argv[1], "name") == 0) {
        char osName[31] = {0};

        int ret = sysinfo_name(osName, 20);

        if (ret != 0) {
            perror(NULL);
            return ret;
        }

        printf("%s\n", osName);
        return 0;
    } else if (strcmp(argv[1], "vers") == 0) {
        char osVers[31] = {0};

        int ret = sysinfo_vers(osVers, 20);

        if (ret != 0) {
            perror(NULL);
            return ret;
        }

        printf("%s\n", osVers);
        return 0;
    } else if (strcmp(argv[1], "ncpu") == 0) {
        int ret = sysinfo_ncpu();

        if (ret < 0) {
            perror(NULL);
            return ret;
        }

        printf("%d\n", ret);
        return 0;
    } else if (strcmp(argv[1], "libc") == 0) {
        int ret = sysinfo_libc();

        if (ret < 0) {
            perror(NULL);
            return ret;
        }

        switch(ret) {
            case 1:  printf("glibc\n"); break;
            case 2:  printf("musl\n");  break;
            default: break;
        }

        return 0;
    } else if (strcmp(argv[1], "euid") == 0) {
        printf("%d\n", geteuid());
        return 0;
    } else if (strcmp(argv[1], "egid") == 0) {
        printf("%d\n", getegid());
        return 0;
    } else {
        fprintf(stderr, "unrecognized argument: %s\n", argv[1]);
        return 1;
    }
}
