#define _DARWIN_C_SOURCE
#define __DARWIN_ONLY_64_BIT_INO_T 0
// int     stat64(const char *, struct stat64 *) __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_5, __MAC_10_6, __IPHONE_NA, __IPHONE_NA);
//
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>

int main() {
    struct stat64 info;
    
    if (stat64("/", &info) != 0) {
        perror("stat64() error");
        return 1;
    } else {
        puts("stat64() returned the following information about root f/s:");
        printf("  inode:   %d\n",   (int) info.st_ino);
        printf(" dev id:   %d\n",   (int) info.st_dev);
        printf("   mode:   %08x\n",       info.st_mode);
        printf("  links:   %d\n",         info.st_nlink);
        printf("    uid:   %d\n",   (int) info.st_uid);
        printf("    gid:   %d\n",   (int) info.st_gid);
        printf("created:   %s",           ctime(&info.st_birthtime));
        return 0;
    }
}
