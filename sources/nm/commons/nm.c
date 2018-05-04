/*
** EPITECH PROJECT, 2018
** nm.c
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
#include "nm.h"

static int elf_format(Elf64_Ehdr *header_d)
{
	if (header_d->e_ident[EI_CLASS] != ELFCLASS64)
		return (-1);
	return (0);
}

static int elf_header(elf_info_t *elf_info)
{
	if (elf_info->elfH_64 && elf_info->elfH_64->e_ident)
		return (memcmp(elf_info->elfH_64->e_ident,
			ELFMAG, strlen(ELFMAG)));
	return (-1);
}

static int elf_parse(int const argc, char const *const name,
			char const *const file, void *map_buf)
{
	elf_info_t elf_info;
	elf_shdr_t elf_shdr;
	elf_sym_t *elf_sym = NULL;

	elf_info.elfH_64 = map_buf;
	if (elf_header(&elf_info) != 0)
		return (error_display(name, file, E_FORMAT));
	if (elf_format(elf_info.elfH_64) == 0) {
		elf_shdr.elfS_64 = (Elf64_Shdr *) ((void *) elf_info.elfH_64 +
						elf_info.elfH_64->e_shoff);
		elf_sym = elf64_sections(elf_info.elfH_64, elf_shdr.elfS_64);
		elf64_display(name, file, &elf_sym, argc);
	} else {
		elf_shdr.elfS_32 = (Elf32_Shdr *) ((void *) elf_info.elfH_32 +
						elf_info.elfH_32->e_shoff);
		elf_sym = elf32_sections(elf_info.elfH_32, elf_shdr.elfS_32);
		elf32_display(name, file, &elf_sym, argc);
	}
	return (list_free_symbols(&elf_sym));
}

int elf_exec(int const argc, char const *const name,
		char const *const file)
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
			return (elf_parse(argc, name, file, map_buf));
		} else
			return (error_display(name, file, E_MMAP));
	} else
		return (error_display(name, file, E_FD));
	return (0);
}
