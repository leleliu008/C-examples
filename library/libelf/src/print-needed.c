#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>

#include <gelf.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <ELF-FILEPATH>\n", argv[0]);
        return 1;
    }

    if (elf_version(EV_CURRENT) == EV_NONE) {
        fprintf(stderr, "libelf initialization failed: %s\n", elf_errmsg(-1));
        return 2;
    }

    int fd = open(argv[1], O_RDONLY, 0);

    if (fd == -1) {
        perror(argv[1]);
        return 3;
    }

    Elf * elf = elf_begin(fd, ELF_C_READ, NULL);

    if (elf == NULL) {
        fprintf(stderr, "elf_begin() failed: %s\n", elf_errmsg(-1));
        close(fd);
        return 4;
    }

    if (elf_kind(elf) != ELF_K_ELF) {
        fprintf(stderr, "NOT an ELF file: %s\n", argv[1]);
        elf_end(elf);
        close(fd);
        return 5;
    }

    size_t phnum;

    if (elf_getphdrnum(elf, &phnum) != 0) {
        fprintf(stderr, "elf_getphdrnum() failed: %s\n", elf_errmsg(-1));
        elf_end(elf);
        close(fd);
        return 6;
    }

    GElf_Phdr phdr;

    int hasDynamic = 0;

    for (size_t i = 0U; i < phnum; i++) {
        if (gelf_getphdr(elf, i, &phdr) != &phdr) {
            fprintf(stderr, "getphdr() failed: %s.", elf_errmsg(-1));
            elf_end(elf);
            close(fd);
            return 7;
        }

        if (phdr.p_type == PT_DYNAMIC) {
            hasDynamic = 1;
            break;
        }
    }

    if (hasDynamic == 0) {
        elf_end(elf);
        close(fd);
        return 0;
    }

    hasDynamic = 0;

    Elf_Scn * scn = NULL;
    GElf_Shdr shdr;

    for (;;) {
        scn = elf_nextscn(elf, scn);

        if (scn == NULL) {
            continue;
        }

        if (gelf_getshdr(scn, &shdr) == NULL) {
            fprintf(stderr, "getshdr() failed: %s.", elf_errmsg(-1));
            elf_end(elf);
            close(fd);
            return 8;
        }

        if (shdr.sh_type == SHT_DYNAMIC) {
            hasDynamic = 1;
            break;
        }
    }

    if (hasDynamic == 0) {
        elf_end(elf);
        close(fd);
        return 0;
    }

    Elf_Data * data = elf_getdata(scn, NULL);

    if (data == NULL) {
        fprintf(stderr, "elf_getdata() failed: %s.", elf_errmsg(-1));
        elf_end(elf);
        close(fd);
        return 9;
    }

    size_t count = shdr.sh_size / shdr.sh_entsize;

    GElf_Dyn dyn;

    for (size_t i = 0U; i < count; i++) {
        if (gelf_getdyn(data, i, &dyn) == NULL) {
            fprintf(stderr, "gelf_getdyn() failed: %s.", elf_errmsg(-1));
            elf_end(elf);
            close(fd);
            return 9;
        }

        if (dyn.d_tag == DT_NEEDED) {
            const char * needed = elf_strptr(elf, shdr.sh_link, dyn.d_un.d_val);
            puts(needed);
        }
    }

    elf_end(elf);
    close(fd);
    return 0;
}
