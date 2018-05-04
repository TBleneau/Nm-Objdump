/*
** EPITECH PROJECT, 2018
** error.c
** File description:
** Created by Thomas BLENEAU
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include "nm.h"

static const char *const error_list[] = {
	[E_FD] = "No such file or directory",
	[E_FILE] = "No such file",
	[E_DIR] = "is a directory",
	[E_FORMAT] = "File format not recognized",
	[E_MMAP] = "mmap",
	[NO_SYM] = "no symbols",
	[E_ACCESS] = "Permission denied"
};

int error_display(char const *const name, char const *const file,
			enum error_e value)
{
	switch(value) {
	case E_FD:
	case E_FILE:
	case NO_SYM:
	case E_ACCESS:
	case E_DIR:
		fprintf(stderr, "%s: Warning: '%s': %s\n",
			name, file, error_list[value]);
		break;
	case E_MMAP:
		perror(error_list[value]);
		break;
	case E_FORMAT:
		fprintf(stderr, "%s: %s: %s\n",
			name, file, error_list[value]);
		break;
	}
	return (-1);
}

int error_file(char const *const name, char const *const file)
{
	struct stat s_file;

	if (access(file, F_OK) == -1)
		return (error_display(name, file, E_FILE));
	if (access(file, R_OK) == -1)
		return (error_display(name, file, E_ACCESS));
	if (stat(file, &s_file) == -1) {
		if (!strcmp(file, "a.out"))
			return (error_display(name, file, E_FILE));
		return (error_display(name, file, E_FD));
	}
	if (S_ISDIR(s_file.st_mode))
		return (error_display(name, file, E_DIR));
	return (0);
}
