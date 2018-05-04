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
#include "objdump.h"

int main(int argc, char **argv)
{
	int ret[3] = {0, 0, -1};
	char **args = NULL;

	if (parse_options(argc, argv) == -1)
		return (1);
	args = (argc == 1) ? single_dup(argc, "a.out") : tab_dup(argc, argv);
	if (args == NULL)
		return (1);
	while (args && args[++ret[2]]) {
		ret[0] = error_file(argv[0], args[ret[2]]);
		if (ret[0] != -1)
			ret[1] = elf_exec(argv[0], args[ret[2]]);
	}
	tab_free(args);
	if (ret[0] == -1 || ret[1] == -1)
		ret[0] = -1;
	return ((ret[0] == -1) ? 1 : 0);
}
