/*
** EPITECH PROJECT, 2018
** tab.c
** File description:
** Created by Thomas BLENEAU
*/

#include <stdlib.h>
#include <string.h>
#include "nm.h"

void tab_free(char **args)
{
	size_t inc = -1;

	while (args && args[++inc])
		free(args[inc]);
	free(args);
}

static char **single_dup(int const argc, char *str)
{
	char **dup = calloc(argc + 1, sizeof(char *));

	if (dup == NULL)
		return (NULL);
	dup[0] = calloc(strlen(str) + 1, sizeof(char));
	if (dup[0] == NULL)
		return (NULL);
	dup[0] = strcpy(dup[0], str);
	dup[argc] = NULL;
	return (dup);
}

char **tab_dup(int const argc, char **argv)
{
	size_t inc[2] = {0, 0};
	char **dup = NULL;

	if (argc == 1) {
		dup = single_dup(argc, "a.out");
		return (dup);
	}
	dup = calloc(argc + 1, sizeof(char *));
	if (dup == NULL)
		return (NULL);
	while (argv && argv[++inc[0]]) {
		dup[inc[1]] = calloc(strlen(argv[inc[0]]) + 1,
				sizeof(char));
		if (dup[inc[1]] == NULL)
			return (NULL);
		dup[inc[1]] = strcpy(dup[inc[1]], argv[inc[0]]);
		inc[1] += 1;
	}
	dup[inc[1]] = NULL;
	return (dup);
}
