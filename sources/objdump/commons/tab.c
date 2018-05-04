/*
** EPITECH PROJECT, 2018
** tab.c
** File description:
** Created by Thomas BLENEAU
*/

#include <stdlib.h>
#include <string.h>
#include "objdump.h"

static const char *const options[] = {
	"-s",
	"--full-contents",
	"-f",
	"--file-headers"
};

void tab_free(char **args)
{
	size_t inc = -1;

	while (args && args[++inc])
		free(args[inc]);
	free(args);
}

static int tab_compare(const char *const name)
{
	int cmp = 0;
	size_t inc = 0;

	while (options[inc] && inc < 4) {
		cmp = strcmp(name, options[inc]);
		if (cmp == 0)
			return (0);
		inc += 1;
	}
	if (cmp != 0)
		return (1);
	return (0);
}

char **single_dup(int const argc, char *str)
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
	char **dup = calloc(argc + 1, sizeof(char *));

	if (dup == NULL)
		return (NULL);
	while (argv && argv[++inc[0]]) {
		if (tab_compare(argv[inc[0]])) {
			dup[inc[1]] = calloc(strlen(argv[inc[0]]) + 1,
						sizeof(char));
			dup[inc[1]] = (dup[inc[1]] == NULL) ? NULL :
				strcpy(dup[inc[1]], argv[inc[0]]);
			inc[1] += 1;
		}
		if (inc[1] > 0 && dup[inc[1] - 1] == NULL)
			return (NULL);
	}
	dup[inc[1]] = NULL;
	return (dup);
}
