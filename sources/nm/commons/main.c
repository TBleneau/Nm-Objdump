/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** Created by Thomas BLENEAU
*/

#include <sys/types.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <locale.h>
#include "nm.h"

int main(int argc, char **argv)
{
	int incr = -1;
	int ret[2] = {0, 0};
	char **args = NULL;

	setlocale(LC_COLLATE, "");
	args = tab_dup(argc, argv);
	if (args == NULL)
		return (1);
	while (args && args[++incr]) {
		ret[0] = error_file(argv[0], args[incr]);
		if (ret[0] != -1)
			ret[1] = elf_exec(argc, argv[0], args[incr]);
	}
	tab_free(args);
	if (ret[0] == -1 || ret[1] == -1)
		ret[0] = -1;
	return ((ret[0] == -1) ? 1 : 0);
}
