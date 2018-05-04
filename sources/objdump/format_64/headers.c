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

static int elf64_display_flags(flags_t **flags)
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

int elf64_header(elf_Ehdr_t const *const elf_Ehdr,
			char const *const file)
{
	flags_t *flags = NULL;

	if (elf_Ehdr && elf_Ehdr->elfH_64) {
		printf("\n%s:     ", file);
		printf("file format elf64-x86-64\n");
		printf("architecture: i386:x86-64, ");
		elf64_header_flags(&flags, elf_Ehdr);
		elf64_display_flags(&flags);
		printf("start address 0x%016lx\n\n",
			elf_Ehdr->elfH_64->e_entry);
		elf64_flags_free(&flags);
	} else
		return (-1);
	return (elf64_sections(elf_Ehdr));
}
