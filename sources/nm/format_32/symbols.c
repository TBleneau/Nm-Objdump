/*
** EPITECH PROJECT, 2018
** symbols.c
** File description:
** Created by Thomas BLENEAU
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <elf.h>
#include <sys/mman.h>
#include "nm.h"

static int list_insert_symbols(elf_sym_t **elf_sym, elf_sym_t *tmp,
				elf_sym_t *new)
{
	if (tmp->prev != NULL)
		tmp->prev->next = new;
	else
		*elf_sym = new;
	new->prev = tmp->prev;
	tmp->prev = new;
	new->next = tmp;
	return (0);
}

static elf_sym_t *list_create_symbols(char const *const name,
					Elf32_Addr const value,
					char const symbol_t)
{
	elf_sym_t *new = calloc(1, sizeof(elf_sym_t));

	if (new == NULL)
		return (NULL);
	new->_name = strdup(name);
	new->symbol = symbol_t;
	new->value = value;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

static int list_add_symbols(elf_sym_t **elf_sym, Elf32_Addr const value,
				char const *const name,
				unsigned char const symbol_t)
{
	elf_sym_t *tmp = *elf_sym;
	elf_sym_t *new = list_create_symbols(name, value, symbol_t);

	if (new == NULL)
		return (-1);
	if (*elf_sym == NULL) {
		*elf_sym = new;
		return (0);
	}
	while (tmp != NULL && tmp->next != NULL) {
		if (strcoll(tmp->_name, new->_name) > 0)
			return (list_insert_symbols(elf_sym,
							tmp, new));
		tmp = tmp->next;
	}
	if (strcoll(tmp->_name, new->_name) > 0)
		return (list_insert_symbols(elf_sym, tmp, new));
	new->prev = tmp;
	tmp->next = new;
	return (0);
}

elf_sym_t *elf32_symbols(Elf32_Sym *symbls, size_t index,
				char *str_tab, Elf32_Shdr *elf_S)
{
	int ret = 0;
	size_t inc = 0;
	unsigned char symbol_t = '?';
	elf_sym_t *elf_sym = NULL;
	size_t size = (elf_S + index)->sh_size / sizeof(Elf32_Sym);

	while (inc < size) {
		if ((str_tab + symbls[inc].st_name)[0] != '\0'
			&& ELF32_ST_TYPE(symbls[inc].st_info) != STT_FILE) {
			symbol_t = elf32_types(symbls[inc], elf_S);
			ret = list_add_symbols(&elf_sym, symbls[inc].st_value,
						str_tab + symbls[inc].st_name,
						symbol_t);
		}
		if (ret == -1)
			return (NULL);
		inc++;
	}
	return (elf_sym);
}
