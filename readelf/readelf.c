/* This is a simplefied ELF reader.
 * You can contact me if you find any bugs.
 *
 * Luming Wang<wlm199558@126.com>
 */

#include "kerelf.h"
#include <stdio.h>
/* Overview:
 *   Check whether it is a ELF file.
 *
 * Pre-Condition:
 *   binary must longer than 4 byte.
 *
 * Post-Condition:
 *   Return 0 if `binary` isn't an elf. Otherwise
 * return 1.
 */
int is_elf_format(u_char *binary)
{
        Elf32_Ehdr *ehdr = (Elf32_Ehdr *)binary;
        if (ehdr->e_ident[EI_MAG0] == ELFMAG0 &&
                ehdr->e_ident[EI_MAG1] == ELFMAG1 &&
                ehdr->e_ident[EI_MAG2] == ELFMAG2 &&
                ehdr->e_ident[EI_MAG3] == ELFMAG3) {
                return 1;
        }

        return 0;
}

/* Overview:
 *   read an elf format binary file. get ELF's information
 *
 * Pre-Condition:
 *   `binary` can't be NULL and `size` is the size of binary.
 *
 * Post-Condition:
 *   Return 0 if success. Otherwise return < 0.
 *   If success, output address of every section in ELF.
 */

unsigned int reversal(unsigned int x)
{
        return (x << 24) | (x << 16 >> 24 << 16) | (x << 8 >> 24 << 8) | (x >> 24);
}

int readelf(u_char *binary, int size)
{
        Elf32_Ehdr *ehdr = (Elf32_Ehdr *)binary;

        // check whether `binary` is a ELF file.
        if (size < 4 || !is_elf_format(binary))
        {
                printf("not a standard elf format\n");
                return 0;
        }

        int Nr;

        Elf32_Off off = ehdr->e_phoff;
        unsigned char type = ehdr->e_ident[5];
        if (type == 2)
                off = reversal(off);
        Elf32_Phdr *phdr = (Elf32_Phdr *)(binary + off);
        Elf32_Half phnum = ehdr->e_phnum;
        if (type == 2)
                phnum = (phnum << 8) | (phnum >> 8);

        for (Nr = 0; Nr < phnum; Nr++, phdr++)
        {
                unsigned int filesize = phdr->p_filesz;
                unsigned int memsize = phdr->p_memsz;
                if (type == 2)
                {
                        filesize = reversal(filesize);
                        memsize = reversal(memsize);
                }
                printf("%d:0x%x,0x%x\n", Nr, filesize, memsize);
        }

        return 0;
}
