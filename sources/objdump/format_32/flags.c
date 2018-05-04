/*
** EPITECH PROJECT, 2018
** flags.c
** File description:
** Created by Thomas BLENEAU
*/

#include <elf.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "objdump.h"
#include "flags.h"

int elf32_flags_free(flags_t **flags)
{
	flags_t *tmp = *flags;
	flags_t *save = NULL;

	while (tmp) {
		save = tmp;
		free(tmp->name);
		tmp = tmp->next;
		free(save);
	}
	return (0);
}

static int elf32_add_flags(flags_t **flags, char const *const name,
				ssize_t const value)
{
	flags_t *tmp = *flags;
	flags_t *new = calloc(1, sizeof(flags_t));

	if (new == NULL)
		return (-1);
	new->name = strdup(name);
	new->value = value;
	new->next = NULL;
	if (*flags == NULL)
		*flags = new;
	else {
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}

static int elf32_flags_sections(flags_t **flags,
				elf_Ehdr_t const *const elf_Ehdr)
{
	int ret = 0;

	if (elf_Ehdr->elfH_32->e_type == ET_REL ||
		elf_Ehdr->elfH_32->e_type == ET_EXEC ||
		elf_Ehdr->elfH_32->e_type == ET_DYN)
		ret = elf32_add_flags(flags, "HAS_SYMS", HAS_SYMS);
	return (ret);
}

int elf32_header_flags(flags_t **flags,
			elf_Ehdr_t const *const elf_Ehdr)
{
	int ret = 0;

	if (elf_Ehdr->elfH_32->e_type == ET_REL)
		ret = elf32_add_flags(flags, "HAS_RELOC", HAS_RELOC);
	if (ret == 0 && elf_Ehdr->elfH_32->e_type == ET_EXEC)
		ret = elf32_add_flags(flags, "EXEC_P", EXEC_P);
	ret = elf32_flags_sections(flags, elf_Ehdr);
	if (ret == 0 && elf_Ehdr->elfH_32->e_type == ET_DYN)
		elf32_add_flags(flags, "DYNAMIC", DYNAMIC);
	if (ret == 0 && (elf_Ehdr->elfH_32->e_type == ET_EXEC
			|| elf_Ehdr->elfH_32->e_type == ET_DYN))
		elf32_add_flags(flags, "D_PAGED", D_PAGED);
	return (ret);
}
