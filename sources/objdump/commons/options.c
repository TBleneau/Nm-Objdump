/*
** EPITECH PROJECT, 2018
** options.c
** File description:
** Created by Thomas BLENEAU
*/

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "objdump.h"

static const char *const options[] = {
	"-s",
	"--full-contents",
	"-f",
	"--file-headers"
};

static void free_options(obj_opt_t **options)
{
	obj_opt_t *tmp = *options;
	obj_opt_t *save = NULL;

	while (tmp) {
		save = tmp;
		free(tmp->name);
		tmp = tmp->next;
		free(save);
	}
}

static int compare_options(const char *const name)
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

static int valid_options(const char *const name, obj_opt_t **options)
{
	int ret = 0;
	obj_opt_t *tmp = *options;

	while (tmp != NULL) {
		if (compare_options(tmp->name)) {
			ret = -1;
			break;
		}
		tmp = tmp->next;
	}
	if (ret == -1)
		error_display(name, tmp->name, E_OPTIONS);
	free_options(options);
	return (ret);
}

static int add_options(obj_opt_t **options, const char *const name,
			char const *const binary)
{
	obj_opt_t *tmp = *options;
	obj_opt_t *new = calloc(1, sizeof(obj_opt_t));

	if (new == NULL) {
		error_display(binary, NULL, E_CALLOC);
		return (-1);
	}
	new->name = strdup(name);
	new->next = NULL;
	new->prev = NULL;
	if (*options == NULL)
		*options = new;
	else {
		while (tmp && tmp->next != NULL)
			tmp = tmp->next;
		new->prev = tmp;
		tmp->next = new;
	}
	return (0);
}

int parse_options(int const argc, char **argv)
{
	int ret = 0;
	int inc = 1;
	obj_opt_t *options = NULL;

	if (argc == 1)
		return (0);
	while (argv && inc < argc) {
		if (argv[inc] && argv[inc][0] == '-')
			ret = add_options(&options, argv[inc], argv[0]);
		if (ret != -1)
			inc += 1;
		else
			break;
	}
	if (ret == -1 || valid_options(argv[0], &options) == -1)
		return (-1);
	return (0);
}
