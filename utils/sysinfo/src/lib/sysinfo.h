#ifndef SYSINFO_H
#define SYSINFO_H

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

typedef struct {
   char * kind;
   char * type;
   char * code;
   char * name;
   char * vers;
   char * arch;
   unsigned int libc;
   unsigned int ncpu;
   uid_t  euid;
   gid_t  egid;
} SysInfo;

int  sysinfo_kind(char * buf, size_t bufSize);
int  sysinfo_type(char * buf, size_t bufSize);
int  sysinfo_code(char * buf, size_t bufSize);
int  sysinfo_name(char * buf, size_t bufSize);
int  sysinfo_vers(char * buf, size_t bufSize);
int  sysinfo_arch(char * buf, size_t bufSize);
int  sysinfo_libc();
int  sysinfo_ncpu();

int  sysinfo_make(SysInfo * sysinfo);
void sysinfo_dump(SysInfo sysinfo);
void sysinfo_free(SysInfo sysinfo);

#endif
