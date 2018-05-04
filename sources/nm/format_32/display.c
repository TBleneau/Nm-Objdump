/*
** EPITECH PROJECT, 2018
** display.c
** File description:
** Created by Thomas BLENEAU
*/

#include <string.h>
#include <stdio.h>
#include <elf.h>
#include <sys/mman.h>
#include "nm.h"

int elf32_display(char const *const name, char const *const file,
		elf_sym_t **elfS, int const argc)
{
	elf_sym_t *tmp = *elfS;

	if (tmp == NULL)
		return (error_display(name, file, NO_SYM));
	if (argc > 2)
		printf("\n%s:\n", file);
	while (tmp != NULL) {
		if (tmp->symbol == 'w' || tmp->symbol == 'U')
			printf("         %c %s\n", tmp->symbol,
				tmp->_name);
		else
			printf("%08lx %c %s\n", tmp->value,
				tmp->symbol, tmp->_name);
		tmp = tmp->next;
	}
	return (0);
}
