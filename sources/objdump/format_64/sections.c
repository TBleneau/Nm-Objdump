/*
** EPITECH PROJECT, 2018
** sections.c
** File description:
** Created by Thomas BLENEAU
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <sys/mman.h>
#include "objdump.h"

static const char *const skip_sections[] = {
	".bss",
	".symtab",
	".strtab",
	".shstrtab"
};

static int valid_sections(char const *const sections)
{
	size_t inc = 0;

	while (skip_sections[inc] && inc < 4) {
		if (strcmp(sections, skip_sections[inc]) == 0)
			return (1);
		inc += 1;
	}
	return (0);
}

static int elf64_sections_display(size_t *index, size_t const size,
					unsigned char *content,
					unsigned char const *const section)
{
	size_t inc[2] = {0, 0};
	size_t index_c = 0;
	size_t index_s = 0;

	while (inc[0] < SECT_CONTENT && *index + inc[0] < size) {
		inc[1] = 0;
		while (inc[1] < FORMAT_CONTENT
			&& *index + inc[0] + inc[1] < size) {
			index_s = *index + inc[0] + inc[1];
			index_c = inc[0] + inc[1];
			elf64_content_update(content, section,
						index_s, index_c);
			inc[1] += 1;
		}
		printf(" ");
		inc[0] += inc[1];
	}
	return (elf64_content_value(index, inc[0], content));
}

static int elf64_sections_content(elf_Ehdr_t const *const elf_Ehdr,
				unsigned char const *const section,
				size_t const index)
{
	unsigned char *content = NULL;
	size_t inc = 0;

	while (inc < elf_Ehdr->elfS_64[index].sh_size) {
		content = elf64_content_init(elf_Ehdr, index, inc);
		if (content == NULL)
			return (-1);
		elf64_sections_display(&inc, elf_Ehdr->elfS_64[index].sh_size,
					content, section);
		free(content);
	}
	return (0);
}

int elf64_sections(elf_Ehdr_t const *const elf_Ehdr)
{
	size_t inc = 0;
	char *sections = NULL;
	unsigned char *content = NULL;
	char *string = (char *) ((void *) elf_Ehdr->elfH_64 +
		elf_Ehdr->elfS_64[elf_Ehdr->elfH_64->e_shstrndx].sh_offset);

	for (inc = 0; inc < elf_Ehdr->elfH_64->e_shnum; inc++) {
		sections = string + elf_Ehdr->elfS_64[inc].sh_name;
		if (sections[0] != '\0' && !valid_sections(sections)) {
			content = (unsigned char *) ((void *) elf_Ehdr->elfH_64
					+ elf_Ehdr->elfS_64[inc].sh_offset);
			printf("Contents of section %s:\n", sections);
			elf64_sections_content(elf_Ehdr, content, inc);
		}
	}
	return (0);
}
