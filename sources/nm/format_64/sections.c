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
#include "nm.h"

static const char SYM_TAB[] = {'.', 's', 'y', 'm', 't', 'a', 'b', '\0'};

static const char STR_TAB[] = {'.', 's', 't', 'r', 't', 'a', 'b', '\0'};

int list_free_symbols(elf_sym_t **elf_sym)
{
	elf_sym_t *tmp = *elf_sym;
	elf_sym_t *save = NULL;

	while (tmp != NULL) {
		free(tmp->_name);
		save = tmp;
		tmp = tmp->next;
		free(save);
	}
	return (0);
}

elf_sym_t *elf64_sections(Elf64_Ehdr *elfH_64, Elf64_Shdr *elf_S)
{
	size_t inc = 0;
	size_t index = 0;
	char *string = (char *) ((void *) elfH_64 +
				elf_S[elfH_64->e_shstrndx].sh_offset);
	char *cmp = NULL;
	char *str_tab = NULL;
	Elf64_Sym *symbls = NULL;

	for (inc = 0; inc < elfH_64->e_shnum; inc++) {
		cmp = string + elf_S[inc].sh_name;
		if (!strcmp(cmp, SYM_TAB)) {
			index = inc;
			symbls = (Elf64_Sym *)
				((void *) elfH_64 + (elf_S + inc)->sh_offset);
		} else if (!strcmp(cmp, STR_TAB))
			str_tab = (char *) ((void *) elfH_64 +
						(elf_S + inc)->sh_offset);
	}
	return (elf64_symbols(symbls, index, str_tab, elf_S));
}
