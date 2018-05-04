/*
** EPITECH PROJECT, 2018
** content.c
** File description:
** Created by Thomas BLENEAU
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <elf.h>
#include "objdump.h"

int elf64_content_value(size_t *index, size_t const number,
			unsigned char const *const value)
{
	size_t inc = number;

	for (inc = number; inc < 16; inc++) {
		if (inc % 4 == 0)
			printf(" ");
		printf("  ");
	}
	printf(" %s\n", value);
	*index += number;
	return (0);
}

unsigned char *elf64_content_init(elf_Ehdr_t const *const elf_Ehdr,
				size_t const index, size_t const size)
{
	unsigned char *cont = calloc(SECT_CONTENT + 1, sizeof(unsigned char));
	unsigned int reference = 0;
	size_t size_sect = elf_Ehdr->elfS_64[index].sh_size;
	size_t pos = (size_sect % 16 == 0) ? 16 : size_sect % 16;
	size_t hexa = elf_Ehdr->elfS_64[index].sh_addr + (size_sect - pos);

	if (cont == NULL)
		return (NULL);
	memset(cont, ' ', SECT_CONTENT);
	if (hexa > 16) {
		while (hexa != 0) {
			hexa = hexa / 16;
			reference += 1;
		}
	}
	reference <= 4 ? printf(" %04lx ",
			elf_Ehdr->elfS_64[index].sh_addr + size) :
		printf(" %0*lx ", reference,
			elf_Ehdr->elfS_64[index].sh_addr + size);
	return (cont);
}

int elf64_content_update(unsigned char *content,
			unsigned char const *const section,
			size_t const index_s,
				size_t const index_c)
{
	printf("%02x", (unsigned char) section[index_s]);
	if ((unsigned char) section[index_s] >= 32
		&& (unsigned char) section[index_s] <= 126) {
		content[index_c] = (unsigned char) section[index_s];
	} else
		content[index_c] = '.';
	return (0);
}
