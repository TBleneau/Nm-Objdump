/*
** EPITECH PROJECT, 2018
** flags.h
** File description:
** Created by Thomas BLENEAU
*/

#ifndef FLAGS_H_
	#define FLAGS_H_

	#include <stddef.h>

	static const ssize_t BFD_NO_FLAGS = 0x00;
	static const ssize_t HAS_RELOC = 0x01;
	static const ssize_t EXEC_P = 0x02;
	static const ssize_t HAS_LINENO = 0x04;
	static const ssize_t HAS_DEBUG = 0x08;
	static const ssize_t HAS_SYMS = 0x10;
	static const ssize_t HAS_LOCALS = 0x20;
	static const ssize_t DYNAMIC = 0x40;
	static const ssize_t WP_TEXT = 0x80;
	static const ssize_t D_PAGED = 0x100;

#endif /* !FLAGS_H_ */
