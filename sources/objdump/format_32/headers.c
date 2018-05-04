/*
** EPITECH PROJECT, 2018
** headers.c
** File description:
** Created by Thomas BLENEAU
*/

#include <elf.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "objdump.h"
#include "flags.h"

static int elf32_display_flags(flags_t **flags)
{
	ssize_t value = 0;
	flags_t *tmp = *flags;

	if (tmp == NULL)
		return (printf("flags 0x%08x:\n%s\n", 0, "BFD_NO_FLAGS"));
	while (tmp) {
		value += tmp->value;
		tmp = tmp->next;
	}
	printf("flags 0x%08lx:\n", value);
	tmp = *flags;
	while (tmp) {
		if (tmp->next != NULL)
			printf("%s, ", tmp->name);
		else
			printf("%s\n", tmp->name);
		tmp = tmp->next;
	}
	return (0);
}

int elf32_header(elf_Ehdr_t const *const elf_Ehdr,
			char const *const file)
{
	flags_t *flags = NULL;

	if (elf_Ehdr && elf_Ehdr->elfH_32) {
		printf("\n%s:     ", file);
		printf("file format elf32-i386\n");
		printf("architecture: i386, ");
		elf32_header_flags(&flags, elf_Ehdr);
		elf32_display_flags(&flags);
		printf("start address 0x%08x\n\n",
			elf_Ehdr->elfH_32->e_entry);
		elf32_flags_free(&flags);
	} else
		return (-1);
	return (elf32_sections(elf_Ehdr));
}
