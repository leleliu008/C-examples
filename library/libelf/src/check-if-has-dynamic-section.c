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

    for (int i = 0; i < phnum; i++) {
        if (gelf_getphdr(elf, i, &phdr) != &phdr) {
            fprintf(stderr, "getphdr() failed: %s.", elf_errmsg(-1));
            elf_end(elf);
            close(fd);
            return 7;
        }

        if (phdr.p_type == PT_DYNAMIC) {
            elf_end(elf);
            close(fd);
            return 0;
        }
    }

    elf_end(elf);
    close(fd);

    fprintf(stderr, "no .dynamic section in file: %s\n", argv[1]);
    return 200;
}
