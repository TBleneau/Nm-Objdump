/*
** EPITECH PROJECT, 2018
** objdump.c
** File description:
** Created by Thomas BLENEAU
*/

#include <string.h>
#include <stdio.h>
#include <elf.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "objdump.h"

static int elf_format(Elf64_Ehdr *header_d)
{
	if (header_d->e_ident[EI_CLASS] != ELFCLASS64)
		return (-1);
	return (0);
}

static int elf_header(elf_Ehdr_t *elf_Ehdr)
{
	if (elf_Ehdr->elfH_64 && elf_Ehdr->elfH_64->e_ident)
		return (memcmp(elf_Ehdr->elfH_64->e_ident,
			ELFMAG, strlen(ELFMAG)));
	return (-1);
}

static int elf_parse(char const *const name,
			char const *const file, void *map_buf)
{
	int ret = 0;
	elf_Ehdr_t elf_Ehdr;

	elf_Ehdr.elfH_64 = map_buf;
	elf_Ehdr.elfS_64 = NULL;
	elf_Ehdr.elfS_32 = NULL;
	if (elf_header(&elf_Ehdr) != 0)
		return (error_display(name, file, E_FORMAT));
	if (elf_format(elf_Ehdr.elfH_64) == 0) {
		elf_Ehdr.elfS_64 = (Elf64_Shdr *) ((void *) elf_Ehdr.elfH_64
					+ elf_Ehdr.elfH_64->e_shoff);
		ret = elf64_header(&elf_Ehdr, file);
	} else {
		elf_Ehdr.elfS_32 = (Elf32_Shdr *) ((void *) elf_Ehdr.elfH_32
					+ elf_Ehdr.elfH_32->e_shoff);
		ret = elf32_header(&elf_Ehdr, file);
	}
	return (ret);
}

int elf_exec(char const *const name, char const *const file)
{
	int file_d;
	void *map_buf;
	struct stat s_file;

	file_d = open(file, O_RDONLY);
	if (file_d != -1) {
		if (stat(file, &s_file) == -1)
			return (error_display(name, file, E_FD));
		map_buf = mmap(NULL, s_file.st_size, PROT_READ,
				MAP_PRIVATE, file_d, 0);
		close(file_d);
		if (map_buf != (void *) -1) {
			return (elf_parse(name, file, map_buf));
		} else
			return (error_display(name, file, E_MMAP));
	} else
		return (error_display(name, file, E_FD));
	return (0);
}
